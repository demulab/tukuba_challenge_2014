wp2action_clientの概要

1.動作
・subsclibeしたwaypoint情報を元にaction_clientを使ってmove_baseにゴールを送信する
・次のwaypoint番号が0より小さい値の場合終了する

2.publishするデータ(goalし終えたwaypoint番号を送る)
	・型：std_msgs::UInt16
	 参考URL: http://ros.org/doc/api/std_msgs/html/msg/Bool.html


3.subclibeするデータ(次に向かうwaypoint)
	・型：geometry_msgs::PoseStamped
	 参考URL: http://www.ros.org/doc/api/geometry_msgs/html/msg/PoseStamped.html
	 --内部構成--
	 header.seq = 次のwaypoint番号
	 pose.potision.x = 次のwaypointのx
	 pose.position.y = 次のwaypointのy
	 pose.position.z = 次のwaypoint番号
	 pose.orientation = 次のwaypointのtheta(rad)
	
	・型：geometry_msgs::PoseWithCovarianceStamped
	amclからpublishされる自己位置を取得 (amclについてはROSwikiを参照のこと)
