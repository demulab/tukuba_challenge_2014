readWayPointsの概要

1.動作
	・waypointをテキストから読みpublishする。
	・goalしたことをsubscribeし、次のwaypointに移行
	・最後のwaypointに到達した場合には、次のwaypoint番号に-1を送る

2.publishされるデータ(次に向かうwaypoint)
	・型：geometry_msgs::PoseStamped
	　参考URL: http://www.ros.org/doc/api/geometry_msgs/html/msg/PoseStamped.html
	　--内部構成--
		header.seq = 次のwaypoint番号
		pose.potision.x = 次のwaypointのx
		pose.position.y = 次のwaypointのy
		pose.position.z = 次のwaypoint番号
		pose.orientation = 次のwaypointのtheta(rad)

3.subscribeするデータ(goalし終えたwaypoint番号を返す
	・型：std_msgs::UInt16
	　参考URL: http://ros.org/doc/api/std_msgs/html/msg/Bool.html

