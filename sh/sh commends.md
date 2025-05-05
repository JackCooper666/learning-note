## open a new terminal
```sh
gnome-terminal -- bash -c "...; exec bash"
```
the "..." is the commend needed to be run

the "exec bash" is to 命令执行完后保持终端不关闭（否则命令一跑完窗口就关了）

## how to run roslaunch and rosbag in one ternimal?
```sh
#!/bin/bash
# Source your ROS workspace environment
source ./devel/setup.bash
# Launch the ROS node in the background

roslaunch fast_livo ac1.launch &

ROSLAUNCH_PID=$!

  

# Wait a few seconds for ROS nodes to fully initialize

sleep 3

  

# Start playing the rosbag

rosbag play ~/zewen/data/NUS/ac1_fastlivo2.bag

  

# Wait for roslaunch to exit (optional, but graceful)

wait $ROSLAUNCH_PID
```


```sh
roslaunch fast_livo ac1.launch &
```
the "&" let the roslaunch to be executed in the back
当你运行一个后台进程时：

```sh
roslaunch fast_livo ac1.launch &
```

Shell 会把这个命令送到后台执行，此时你可以用 `$!` 来获取**刚刚放入后台的最后一个进程的 PID**：

```sh
ROSLAUNCH_PID=$!
```

这行代码就把 roslaunch 的进程号保存进变量 `ROSLAUNCH_PID`。

use the 
```sh
wait $ROSLAUNCH_PID
```
to stack the terminate of the whole sh code until the rosbag done

