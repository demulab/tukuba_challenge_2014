#ifndef SEARCH_TASK_H
#define SEARCH_TASK_H


#include <tf/transform_listener.h>
#include <geometry_msgs/PoseStamped.h>
#include <fstream>

namespace task_manager{

    // task state
    enum TargetDetectionState{
        SEARCH_TARGET,
        SEARCH_TARGET_TURN,
        TOWARDS_TARGET,
        WAITING_AT_TARGET,
    };

    // turn direction
    enum TurnDirection{
        LEFT,
        RIGHT,
    };

	struct SectionPoint{
		public:
		int start;
		int end;
		SectionPoint(int _start, int _end){
			start = _start;
			end = _end;
		}
		SectionPoint(){
			start = 0;
			end = 0;
		}
	};


    class SearchTask{
        private:

            geometry_msgs::PoseStamped detect_target;
            geometry_msgs::PoseStamped turn_point;
            tf::TransformListener tflistener;

            TargetDetectionState state;
            const double error_thresh;    // 1.5[m]以内のぶれは許容する: ボツ
			TurnDirection turn_dir;

			std::ofstream *target_out;

        public:
            ros::Subscriber target_sub;
            ros::Publisher turn_navi;

            SearchTask() : state(SEARCH_TARGET),error_thresh(1.5)
            {
				target_out = new std::ofstream("human_point.dat");
            }

            TargetDetectionState 
            getState(void)
            {
                return state;
            }

            void
            turnSearch(TurnDirection dir)
            {
                double angular;
                if(dir == LEFT)
                {
                    angular = 8.3*M_PI/180;
                }
                else
                {
                    angular-= -8.3*M_PI/180;
                }
                geometry_msgs::Twist turn_vel;
                turn_vel.angular.z = angular;
                turn_navi.publish(turn_vel);
				turn_dir = dir;
			}

            void 
            targetCallBack(const geometry_msgs::PoseStamped target)
            {

                geometry_msgs::PoseStamped trans_target, old_target,target_;
                target_ = target;
                target_.header.frame_id = "base_link";
                // 座標変換
                tflistener.transformPose("/map",target_.header.stamp,target_, "/base_link", trans_target);

                old_target = detect_target;
                detect_target = trans_target;
                //std::cout << detect_target.pose.position.x << " ," << detect_target.pose.position.y << std::endl;
            }

            /*
             * @brief 状態遷移関数
             *
             * [Search Target] <-------> [Search Target Turn]
             *     ^  ^                           |
             *     |  |                           |
             *     |  |                           |
             *     |  |                           V
             *     |  +-----------------> [Towards Target]
             *     |                              |
             *     |                              |
             *     |                              |
             *     |                              V
             *     +------------------- [Waiting At Target]
             */

            void 
            switchState(geometry_msgs::PoseStamped robot,geometry_msgs::PoseStamped waypoint)
            {
                TargetDetectionState current_state = state;
                static int step = 0;
				if(step == 0){
                    std::cout << "Search target ..." << std::endl;
					step++;
				}
				switch(current_state){
                    case SEARCH_TARGET:
                        if(checkGoal(robot, waypoint, 0.5)){
                            turn_point = robot;
                            state = SEARCH_TARGET_TURN;
                            std::cout << std::endl << "Search target Turn ..." << std::endl << std::endl;
                        }
                        if(detect_target.pose.position.x != 0 && detect_target.pose.position.y != 0){
                            state = TOWARDS_TARGET;
                            std::cout << std::endl << "Towards target ..." << std::endl <<std::endl;
                        }
						break;
 
					case SEARCH_TARGET_TURN:
                         if(checkTurn(robot, 5*M_PI/180)){
                            state = SEARCH_TARGET;
                            std::cout << std::endl << "Search target ..." << std::endl << std::endl;
                        }

                        if(detect_target.pose.position.x != 0 && detect_target.pose.position.y != 0){
                            state = TOWARDS_TARGET;
                            std::cout  << std::endl << "Towards target ..." << std::endl <<std::endl;
                        }

                    break;
 
                    case TOWARDS_TARGET:
                        if(checkGoal(robot, detect_target, 1.2)){
                            state = WAITING_AT_TARGET;
                            std::cout << std::endl << "Waiting at target ..." << std::endl << std::endl;
                        }
                    break;
                    case WAITING_AT_TARGET:
                        state = SEARCH_TARGET;
                        detect_target.pose.position.x = 0;
                        detect_target.pose.position.y = 0;
                    break;
                }
            }

            geometry_msgs::PoseStamped
            getTaskGoal(geometry_msgs::PoseStamped robot_pose, geometry_msgs::PoseStamped waypoint)
            {
                geometry_msgs::PoseStamped goal;
                // エラーデータ
                goal.pose.position.x = -1;
                goal.pose.position.y = -1;
                goal.pose.position.z = -1;

                switchState(robot_pose,waypoint);

                switch(state){
                    case SEARCH_TARGET:
                        goal = waypoint;
                    break;
                    case SEARCH_TARGET_TURN:
                    break;
                    case TOWARDS_TARGET:
                        goal = detect_target;
                    break;

                    case WAITING_AT_TARGET:
                    break;
                }
                return goal;
            }
/*
            geometry_msgs::PoseStamped
            searchTarget(geometry_msgs::PoseStamped robot, geometry_msgs::PoseStamped waypoint)
            {
                if(checkGoal(robot,waypoint,0.5)){
                    double wp_yaw = tf::getYaw(waypoint.pose.orientation);
                    double rb_yaw = tf::getYaw(robot.pose.orientation);
                    // 回転が終了したかどうか
                    if(fabs(wp_yaw-rb_yaw) < 10*M_PI/180){
                        return waypoint;
                    }
                    // 回転の割りこみデータを生成
                    wp_yaw += M_PI-1*M_PI/180;
                    waypoint.pose.orientation = tf::createQuaternionMsgFromYaw(wp_yaw);

                    return waypoint;
                }
                else{
                    return waypoint;
                }
            }
*/
            bool 
            checkGoal(geometry_msgs::PoseStamped robot, geometry_msgs::PoseStamped goal, double thresh)
            {
                double diff_x = robot.pose.position.x - goal.pose.position.x;
                double diff_y = robot.pose.position.y - goal.pose.position.y;
                double dist = sqrt(diff_x * diff_x + diff_y * diff_y);
                if(dist < thresh)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }

            bool 
            checkTurn(geometry_msgs::PoseStamped robot,double thresh)
            {
                double rb_yaw = tf::getYaw(robot.pose.orientation);
				double end_yaw; 
				if(turn_dir == LEFT){
					end_yaw = conv_angle(tf::getYaw(turn_point.pose.orientation)-thresh-10*M_PI/180);
				}
				else{
					end_yaw = conv_angle(tf::getYaw(turn_point.pose.orientation)+thresh+10*M_PI/180);
				}
				if(fabs(rb_yaw - end_yaw) < thresh)
                {
                    return true;
                }
                else{
                    return false;
                }
            }

			double 
			conv_angle(double rad)
			{
				if(rad > M_PI) rad = rad - 2.0*M_PI;
				if(rad < -M_PI) rad = rad + 2.0*M_PI;
				return rad;
			}
			void dataOut(int section,double x, double y){
				*target_out << "Section --> " << section << " : [ "<< x << " , " << y << " ]" << std::endl;
			}
    };


} // namespace task_manager

#endif 
