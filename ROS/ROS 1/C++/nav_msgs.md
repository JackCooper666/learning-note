# nav_msgs/Path.h
the nav_msgs/Path type stores the states of robot until current frame.
before use it the library should be included.
```cpp
#include<nav_msgs/Path.h>
```
if you want to get the current pose of the robot, this is a example
```cpp
#include <ros/ros.h>

#include <geometry_msgs/PoseStamped.h>

#include <nav_msgs/Odometry.h>

#include <nav_msgs/Path.h>

#include <fstream>

#include <unordered_set>

#include <mutex>

#include <iomanip>

#include <sys/stat.h>

#include <ros/package.h>

#include <string>

using namespace std;

  

mutex buffer_mutex;

unordered_set<double> recorded_timestamps; // To track duplicates

ofstream out_file;

  

struct Entry {

double time;

double tx, ty, tz;

double qx, qy, qz, qw;

};

  

void saveEntry(const Entry& e) {

out_file << std::fixed << std::setprecision(6) << e.time << " "

<< e.tx << " " << e.ty << " " << e.tz << " "

<< e.qx << " " << e.qy << " " << e.qz << " " << e.qw << "\n";

}

  

void processEntry(const Entry& e) {

std::lock_guard<std::mutex> lock(buffer_mutex);

// Check for duplicate timestamp

if (recorded_timestamps.find(e.time) == recorded_timestamps.end()) {

recorded_timestamps.insert(e.time);

saveEntry(e);

} else {

ROS_WARN_STREAM("Duplicate timestamp detected and skipped: " << e.time);

}

}

  
  

void Callback(const nav_msgs::Path::ConstPtr& msg){

if (!msg->poses.empty()) {

// Use the last pose in the path

const auto& last_pose = msg->poses.back();

Entry e;

e.time = last_pose.header.stamp.toSec();

e.tx = last_pose.pose.position.x;

e.ty = last_pose.pose.position.y;

e.tz = last_pose.pose.position.z;

e.qx = last_pose.pose.orientation.x;

e.qy = last_pose.pose.orientation.y;

e.qz = last_pose.pose.orientation.z;

e.qw = last_pose.pose.orientation.w;

processEntry(e);

}

}
```