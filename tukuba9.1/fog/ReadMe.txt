date : 2012.12.04
author : Shohei TAKESAKO

機能
 FOG(光ファイバージャイロ)のデータを読み込み,odom(pkg名)とserviceとclientの関係で通信

動作
 毎動作の最初に、FOGのオフセットを行う必要がある。
 しかし、基本的にはodom(pkg名)が自動で行うので、意識する必要はない。
 詳しくはodom内のReadMeを参照のこと。

 参照
 roscd launch/wp_navi/
 sensorSet.launch内と同じ使い方をしてもらえれば、後は勝手に動作します。
 コメントアウトされている場合もあるので、その点には注意。
