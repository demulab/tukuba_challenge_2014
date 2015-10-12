date : 2012.12.04
author : Shohei TAKESAKO

機能
 エンコーダの値とFOGの値からodometryを算出し、publishする。(エンコーダのみでも動作可能。しかしその場合、姿勢の制度は著しく低下する。)
 
動作
 FOGを使用するかは、defineで切り替えられる。(src/main.cpp内に宣言されている。) 
 FOGを使用する場合、pkgを起動した最初にオフセットの設定を行うので、ロボットに触れないようにすること。
 以下に手順を示す。

 1. odom, fog, wheel を起動
 
 2. odomを起動した端末に"オフセット中です。ロボットに触れないでください"と表示される
 
 3. 端末の画面が止まった後、odometryが以下のように表示される。
	odom_x, odom_y, odom_theta, distance
	0.0[m], 0.0[m], 0.0[deg], 0.0[m]
 
 4. 表示されたあと、ロボットを少し揺らす。
 
 5. 表示が以下のようになることを確認する。
	odom_x, odom_y, odom_theta, distance
	0.0[m], 0.0[m], 0.021(値が変わる)[deg], 0.0[m]
 
 6. 値が変わらない場合は、また待機していると、「2.」の文字が表示されるので、「3.」からやり直す。

 7. 値が変わるが、ロボットを触らない状態で値が常に変わるのは、オフセットに失敗したことによる影響なので、「1.」からやり直す。

 8. 「6.」「7.」に当てはまらない場合は、起動成功。 実験を開始してください。

通信関係
 wheel(pkg名)とfog(pkg名)とserviceとclientの関係でデータをやりとりする。

 publish
  "odom"		nav_msgs::Odometry型のデータ(ROSの座標系に準拠)スタートから現在までのodometry(推奨)
  "odom_rad"	nav_msgs::Odometry型のデータ(2011年度卒業の平井雄一郎が作成したlaser_to_mapping用の座標系になっているため、ROSの座標系と異なる。基本的に使用禁止)
  "odom_diff"	nav_msgs::Odometry型のデータ odometryの前回分との差分データ(よくよく考えたら、publishは受信側と同期していないので無駄 XD)


