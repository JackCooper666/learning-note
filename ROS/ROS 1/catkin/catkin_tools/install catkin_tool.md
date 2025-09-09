# the components in catkin_tool
catkin_tools 是对 ROS 原始构建系统 catkin_make 的一个现代化、功能更强的替代品。它提供了一套名为 catkin 的命令来构建 ROS 工作空间。

主要作用
编译和构建：它的核心功能是编译工作空间 src 目录下的所有 ROS 包，生成可执行文件、库文件和消息类型等。
改进的构建流程：相比于 catkin_make，catkin_tools 提供了许多改进：
并行构建：可以同时编译多个包，大大加快了大型工作空间的编译速度。
隔离构建：每个包都在一个独立的环境中编译，避免了包之间的意外干扰，使得调试更加容易。
更友好的输出：构建过程的输出信息更加清晰、整洁，一目了然地显示每个包的编译进度和状态。
工作空间隔离：生成的 build 和 devel 目录会带有特定的配置文件名，方便在多个工作空间之间切换，而不会相互影响。
常用命令
假设你在工作空间的根目录下（例如 ~/catkin_ws/）：

catkin build: 编译整个工作空间。这是最核心的命令。
catkin clean: 清理构建产生的所有中间文件和目标文件（相当于 rm -rf build/ devel/ logs/）。
catkin build my_package_name: 只编译指定的包及其依赖项。
catkin create pkg my_new_pkg --catkin-deps roscpp rospy std_msgs: 创建一个新的 ROS 包，并自动在 package.xml 中添加依赖。
catkin config: 查看或修改工作空间的构建配置（例如编译选项 CMAKE_BUILD_TYPE 等）。
总结：catkin_tools 是一个纯粹的构建工具，它假设源代码已经存在于 src 目录中。
————————————————
版权声明：本文为CSDN博主「Tipriest_」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/titan__/article/details/150067837

# Installing on Ubuntu with apt-get[¶](https://catkin-tools.readthedocs.io/en/latest/installing.html#installing-on-ubuntu-with-apt-get "Link to this heading")

First you must have the ROS repositories which contain the `.deb` for `catkin_tools`:
```bash
$ sudo sh \
    -c 'echo "deb http://packages.ros.org/ros/ubuntu `lsb_release -sc` main" \
        > /etc/apt/sources.list.d/ros-latest.list'
$ wget http://packages.ros.org/ros.key -O - | sudo apt-key add -
```
Once you have added that repository, run these commands to install `catkin_tools`:
```bash
$ sudo apt-get update
$ sudo apt-get install python3-catkin-tools
```