# compile prepare
## 1）包含头文件
```cpp
#include <ros/package.h>
```
## 2）修改CMakeLists.txt文件

（1）在find_package()添加roslib，如下所示：
```cpp
find_package(catkin REQUIRED COMPONENTS 
roscpp 
rospy 
roslib 
)
```
（2）在target_link_libraries()中添加${catkin_LIBRARIES}，如下所示：
```cpp
target_link_libraries(pcd_read ${catkin_LIBRARIES})
```
## 3）修改package.xml文件
```cpp
<build_depend>roslib</build_depend> <exec_depend>roslib</exec_depend>
<depend>rospack</depend>
```
# Functions
## ros::package::getPath
ros中用于获取某个功能包的绝对路径，当功能包不存在时，该函数返回一个空的字符串。其函数原型如下：
```cpp
std::string ros::package::getPath (const std::string &package_name)
```
### 正确用法

最后，可以在源代码文件中按照如下方式使用：
```cpp
std::string pcdFileName = ros::package::getPath("convert_las2pcd") + "/pcd/pointcloud.pcd";
pcl::io::savePCDFileASCII(pcdFileName.c_str(), cloud);
```