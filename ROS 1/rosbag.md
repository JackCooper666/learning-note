#### 1 rosbag话题录制

```bash
rosbag record -a #录制所有的话题
rosbag record -a test.bag #录制所有的话题，到指定包名下

rosbag record /topic1 /topic2 -o  #录制指定话题
rosbag record /topic1 /topic2 -o text.bag #录制指定话题，到指定包名下
```

#### 2 rosbag信息查看

```bash
rosbag info 包名.bag  #查看录制包的信息
rosbag play 包名.bag  #播放录制包
```

#### 3 rosbag转换格式（bag2txt）

```bash
rostopic echo -b file_name.bag -p /topic_name > Txt_name.txt
#在bag下将指定话题转换成txt
```

#### 4 rosbag截取录制时间

```bash
rosbag filter input.bag output.bag "t.secs <= 1284703931.86"
#截取1284703931.86（机器时间）之前时刻
rosbag filter input.bag output.bag "t.secs >= 1531425960 and t.secs <= 1531426140"
#截取所设置的时间范围内rosbag
```