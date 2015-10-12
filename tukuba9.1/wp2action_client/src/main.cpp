/*      read waypoints                      */
/*      author shohei TAKESAKO              */
/*      last update : 2012.11.14            */
/*	update : 2015.9.29		    */

#include <iostream>
#include "MyMethod.h"
#include <ros/ros.h>
#include <std_msgs/UInt32.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/scoped_ptr.hpp>

#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "actionlib/client/action_client.h"
#include "actionlib/client/simple_goal_state.h"
#include "actionlib/client/simple_client_goal_state.h"
#include "actionlib/client/terminal_state.h"
#include "actionlib/client/comm_state.h"

#include "move_base/move_base.h"

#include "search_task.h"


#define TIMEOUT 10.0
#define YAW_TIMEOUT 15
#define HZ 10//5
#define SUPPORT_LENGTH 1.5
#define SUPPORT_X 0.2 
#define SUPPORT_Y 0.2 
//#define GOAL_LENGTH 0.9
#define GOAL_LENGTH 1.0
#define SEARCHWPCOUNT 15.0 //2015.09.29西川追加
using namespace std;

typedef actionlib::ActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
typedef actionlib::ClientGoalHandle<move_base_msgs::MoveBaseAction> GoalHandleT;

//subscribeしたwaypoint情報
geometry_msgs::Pose nextWayPoint;
int nextWpNum=0;
//subscribeした自己位置情報
geometry_msgs::PoseStamped robotPose; //ロボットの自己位置 
//subscrubeした速度
double navi_vel_x=0.0;
double navi_vel_y=0.0;
double navi_vel_theta=0.0;


//コールバック関数
//現在のウェイポイント番号を取得する関数
void nextWpCallback(const geometry_msgs::PoseStamped nextWp)
{
    //magsの構造上の問題で、メンバzにウェイポイント番号を格納しているため
    nextWpNum = nextWp.pose.position.z;
    nextWayPoint.position= nextWp.pose.position;
    nextWayPoint.position.z= 0.0;
    nextWayPoint.orientation= nextWp.pose.orientation;
//  cout<< "nextWpCallback" <<endl; 
}

//コールバック関数
//現在の自己位置を得る
void amcl_poseCB(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
{
    robotPose.header = msg->header;
    robotPose.pose = msg->pose.pose;
    cout << "robotPose.pose.position.x = " << robotPose.pose.position.x << endl;
    cout << "robotPose.pose.position.y = " << robotPose.pose.position.y << endl;
}

void naviCallback(const geometry_msgs::Twist navi)
{

//  cout << "navi.linear.x  = " << navi.linear.x << endl;
//  cout << "navi.linear.y  = " << navi.linear.y << endl;
//  cout << "navi.linear.z = " << navi.linear.z << endl;
//  cout << "navi.angular.x = " << navi.angular.x << endl;
//  cout << "navi.angular.y = " << navi.angular.y << endl;
//  cout << "navi.angular.z = " << navi.angular.z << endl;
    
    navi_vel_x = navi.linear.x;
    navi_vel_y = navi.linear.y;
    navi_vel_theta =navi.angular.z;
}


int main(int argc, char **argv)
{
    //ROSの初期化
    ros::init(argc, argv, "Wp2MoveBase");
    ros::NodeHandle n;
/*
    int start_point = 2;
    int end_point = 4;
*/
    //goal用Handle
    GoalHandleT gh_;

    //action_clientのオブジェクト作成
    boost::scoped_ptr<MoveBaseClient> ac_;
    ros::CallbackQueue callback_queue;
        
    ac_.reset(new MoveBaseClient(n, "move_base", &callback_queue)); 
    gh_.reset();
/*
    ros::NodeHandle nh("~");
    ros::ServiceClient client_costmap = nh.serviceClient<std_srvs::Empty>("clear_costmaps");
    std_srvs::Empty costmap_clear;
*/
    //Publishの設定
    std_msgs::UInt32 nowWayPointNum;
	std_msgs::UInt32 Diff_Length;
    ros::Publisher pubNowWayPointsNum = n.advertise<std_msgs::UInt32>("nowWayPointNum", 100);
    ros::Publisher pubdiff_length = n.advertise<std_msgs::UInt32>("diff_length", 100);

    //Subscribeの設定
    ros::Subscriber next_wp_sub = n.subscribe("nextWayPoint", 1, nextWpCallback);
    ros::Subscriber amcl_pose_sub_ = n.subscribe<geometry_msgs::PoseWithCovarianceStamped>("amcl_pose",1, amcl_poseCB);
    //ros::Subscriber amcl_pose_sub_ = n.subscribe<geometry_msgs::PoseWithCovarianceStamped>("amcl_pose_gps",1, amcl_poseCB);
    ros::Subscriber navSub = n.subscribe("cmd_vel", 1, naviCallback);   
    
    //move_baseに送るデータ
    move_base_msgs::MoveBaseGoal goal;
    //前回送ったゴール
    move_base_msgs::MoveBaseGoal lastGoal;


    //変数の宣言
    int nowWp=0;//通過したウェイポイント番号
    nowWayPointNum.data = nowWp;

    //初期設定
    goal.target_pose.header.frame_id = "/map";
    goal.target_pose.header.stamp = ros::Time::now();
    lastGoal = goal;

    geometry_msgs::Pose lastNextWayPoint;//前ループの目標位置
    lastNextWayPoint.position.x =0.0;
    lastNextWayPoint.position.y =0.0;

    geometry_msgs::PoseStamped lastRobotPose; //前ループのロボットの自己位置 
    lastRobotPose.pose.position.x = 0.0;
    lastRobotPose.pose.position.y = 0.0;
    
    double timeCount=0.0;
    double searchWpCount = 0.0;
    task_manager::SearchTask human_task;
    human_task.target_sub = n.subscribe("detect_target",100, &task_manager::SearchTask::targetCallBack, &human_task);
    human_task.turn_navi = n.advertise<geometry_msgs::Twist>("cmd_vel", 100);
	const int section_num = 1;
	task_manager::SectionPoint task_section[section_num];

	// 探索区間の初期化
	task_section[0] = task_manager::SectionPoint(21,30);	// waypoint[21, 30]で人物をさがす
	//task_section[1] = task_manager::SectionPoint(38,78);
	//task_section[2] = task_manager::SectionPoint(38,78);

    //繰り返し処理
    while(ros::ok())
    {
        if(nextWpNum < 0)
        {
            nowWayPointNum.data = nextWpNum;
            pubNowWayPointsNum.publish(nowWayPointNum);
            break;
        }

		for(int i=0; i<section_num; i++){

        // 人物検出タスク
        if(task_section[i].start <= nowWp && nowWp < task_section[i].end){
            geometry_msgs::PoseStamped waypoint;
            waypoint.pose = nextWayPoint;
            move_base_msgs::MoveBaseGoal task_goal;


            task_goal.target_pose.header.frame_id = "/map";
            task_goal.target_pose.header.stamp = ros::Time::now();
            task_goal.target_pose.pose = human_task.getTaskGoal(robotPose, waypoint).pose;

            /*
             *
             * 状態遷移@ TukubaChallenge 2013
             *
             */
            // タスク終了処理
            if(human_task.getState() == task_manager::WAITING_AT_TARGET)
            {
                //探索エリアの最終地点を目的地に設定 ボツ
                //nowWp=end_point-1;
            
                // 全探索に変更
				nowWp=nextWpNum;
                nowWayPointNum.data = nowWp;
                pubNowWayPointsNum.publish(nowWayPointNum);

                ROS_INFO("---- > Now waiting");
                //一時停止処理
                task_goal.target_pose.pose.position.x = robotPose.pose.position.x;
                task_goal.target_pose.pose.position.y = robotPose.pose.position.y;
                task_goal.target_pose.pose.orientation = robotPose.pose.orientation;
                gh_ = ac_->sendGoal(goal);
                //usleep(5*1000*1000);
                sleep(5);
                ac_->cancelAllGoals();
                gh_.cancel();
				human_task.dataOut(i,task_goal.target_pose.pose.position.x,task_goal.target_pose.pose.position.y);
                ROS_INFO("---- > next search point");

				// コールバックを有効に
				ros::spinOnce();
                continue;
            }
            else if(human_task.getState() == task_manager::TOWARDS_TARGET)
            {
                //ac_->cancelAllGoals();
                //gh_.cancel();
                gh_ = ac_->sendGoal(task_goal);
				// コールバックを有効に
				ros::spinOnce();
                continue;
            }
            else if(human_task.getState() == task_manager::SEARCH_TARGET_TURN)
            {
                human_task.turnSearch(task_manager::LEFT);
				// コールバックを有効に
				ros::spinOnce();
                continue;
            }
        }
		}

        //timeCount += 1.0/(double)HZ;
        double diff_x = nextWayPoint.position.x - robotPose.pose.position.x;
        double diff_y = nextWayPoint.position.y - robotPose.pose.position.y;
        double diff_length = sqrt(pow(diff_x, 2.0) + pow(diff_y, 2.0));
        cout << "now pos x :" << robotPose.pose.position.x << " y :" << robotPose.pose.position.y << endl;
		cout << "diff length :" << diff_length << endl;
		Diff_Length.data = diff_length;
        pubdiff_length.publish(Diff_Length);

		//double diff_theta = tf::getYaw(nextWayPoint.pose.orientation) - tf::getYaw(robotPose.pose.orientation);   
        
        actionlib::CommState comm_state_ =  gh_.getCommState();
        /*switch( comm_state_.state_)
        {
            case actionlib::CommState::WAITING_FOR_GOAL_ACK:
                cout<< "WAITING_FOR_GOAL_ACK" <<endl;   break;
            case actionlib::CommState::PENDING:
                cout<< "PENDING" <<endl;    break;
            case actionlib::CommState::RECALLING:
                cout<< "RECALLING" <<endl;  break;
            case actionlib::CommState::ACTIVE:
                cout<< "ACTIVE" <<endl;     break;
            case actionlib::CommState::PREEMPTING:
                cout<< "PREEMPTING" <<endl; break;
            case actionlib::CommState::DONE:
                cout<< "DONE" <<endl;       break;
            default :
                cout << "default" <<endl;
        }
        */
        if(nextWpNum > nowWp)
        {
            //move_baseに送信
            goal.target_pose.pose.position = nextWayPoint.position;
            goal.target_pose.pose.orientation = nextWayPoint.orientation;
            //goal.target_pose.pose.orientation = robotPose.pose.orientation;
            //ゴール前で停止するのを防ぐ処理
            if(diff_length < SUPPORT_LENGTH)
            {
                goal.target_pose.pose.position.x += (diff_x / fabs(diff_x)) * SUPPORT_X; // SUPPORT_X[m]先にゴールをずらす  
                goal.target_pose.pose.position.y += (diff_y / fabs(diff_y)) * SUPPORT_Y; // SUPPORT_Y[m]先にゴールをずらす  
                //gh_ = ac_->sendGoal(goal);
            }
            /*
            if(timeCount > TIMEOUT)
            {
                if((navi_vel_x != 0.0)||(navi_vel_y != 0.0))
                {
                    timeCount = 0.0;
                }
                //timeCount = 0;    
            }
            */
            if(((navi_vel_x == 0.0)&&(navi_vel_y == 0.0)&&(navi_vel_theta == 0.0)) && (comm_state_.state_ == actionlib::CommState::WAITING_FOR_GOAL_ACK))
            {
                cout<< "Goal is not found or stuck" <<endl;
                timeCount += 1.0/(double)HZ;
	        /*2015.09.30*/
		searchWpCount += 1.0/(double)HZ;
		if(searchWpCount > SEARCHWPCOUNT)
		{
		   nowWp = nextWpNum;
		   searchWpCount = 0.0;
		}
            }
            //else if(!(lastNextWayPoint.position.x == nextWayPoint.position.x && lastNextWayPoint.position.y == nextWayPoint.position.y))
            else if(!(goal.target_pose.pose.position.x == lastGoal.target_pose.pose.position.x && goal.target_pose.pose.position.y == lastGoal.target_pose.pose.position.y))
            {   
                gh_ = ac_->sendGoal(goal);
                timeCount = 0.0;
            }

            if(timeCount > TIMEOUT)
            {   
                gh_ = ac_->sendGoal(goal);
                timeCount = 0.0;
            }
                
        /*
            if(lastRobotPose.pose.position.x == robotPose.pose.position.x && lastRobotPose.pose.position.y == robotPose.pose.position.y)
            {   timeCount += 1.0/(double)HZ;    }
            else
            {   
                lastRobotPose = robotPose;
                timeCount = 0.0;
            }
        */
        }
        lastNextWayPoint = nextWayPoint;
        //lastRobotPose = robotPose;
        //double wp_theta = tf::getYaw(nextWayPoint.orientation);
        //double local_theta = tf::getYaw(robotPose.pose.orientation);
        //double diff_theta = fabs(local_theta - wp_theta);
        //if((diff_length < 0.5) && (diff_theta*180/M_PI < 20.0))
        
        if(diff_length < GOAL_LENGTH)
        {
            if(nextWpNum > nowWp)
            {   
                nowWp=nextWpNum;
                ROS_INFO("Goal WayPoint -> %d", nowWp);
                //ゴールしたことをpublish
                nowWayPointNum.data = nowWp;
                pubNowWayPointsNum.publish(nowWayPointNum);
                //一時停止処理
                //goal.target_pose.pose.position.x = robotPose.pose.position.x;
                //goal.target_pose.pose.position.y = robotPose.pose.position.y;
                //goal.target_pose.pose.orientation = robotPose.pose.orientation;
                //gh_ = ac_->sendGoal(goal);
                //usleep(1*1000*1000);
                ac_->cancelAllGoals();
                gh_.cancel();
                gh_.reset();
                /*
                //次のwaypointに切り替わるまで待つ
                while(ros::ok())
                {
                    if(nextWpNum > nowWp)
                    {   break;  }
                    ros::Rate loop_rate(HZ);
                    loop_rate.sleep();
                    ros::spinOnce();
                }
                //姿勢の調整
                double yawCount=0;
                while(ros::ok())
                {   
                    if(fabs(tf::getYaw(nextWayPoint.orientation) - tf::getYaw(robotPose.pose.orientation)) < 15.0*M_PI/180.0)
                    {   break;  }
                    else if(yawCount > YAW_TIMEOUT)
                    {   break;  }
                    goal.target_pose.pose.position.x = robotPose.pose.position.x;
                    goal.target_pose.pose.position.y = robotPose.pose.position.y;
                    goal.target_pose.pose.orientation = lastNextWayPoint.orientation;
                    gh_ = ac_->sendGoal(goal);
                    ros::Rate loop_rate(HZ);
                    loop_rate.sleep();
                    ros::spinOnce();
                    yawCount += 1.0/(double)HZ;
                }
                
                //一時停止処理
                goal.target_pose.pose.position.x = robotPose.pose.position.x;
                goal.target_pose.pose.position.y = robotPose.pose.position.y;
                goal.target_pose.pose.orientation = robotPose.pose.orientation;
                gh_ = ac_->sendGoal(goal);
                ac_->cancelAllGoals();
                gh_.cancel();
                gh_.reset();
                */
            }   
        }
        //cout<< "main main main main main main" <<endl;
        //cout<< "nextWpNum = " << nextWpNum <<endl;
        nowWayPointNum.data = nowWp;
        pubNowWayPointsNum.publish(nowWayPointNum);
        
        if(nextWpNum == nowWp)
        {
            //gh_.reset();
            //usleep(4*1000*1000);
        }
        else
        { 
            ros::Rate loop_rate(HZ);
            loop_rate.sleep();
        }
        lastGoal = goal;
        ros::spinOnce();
    }
    
    //終了処理
    goal.target_pose.pose.position.x = robotPose.pose.position.x;
    goal.target_pose.pose.position.y = robotPose.pose.position.y;
    goal.target_pose.pose.orientation = robotPose.pose.orientation;
    gh_ = ac_->sendGoal(goal);
    
    usleep(1*1000*1000);

    ac_->cancelAllGoals();
    gh_.cancel();
    gh_.reset();
    ac_.reset();
    cout << "wp2action_client is end." << endl;

    return 0;
}

