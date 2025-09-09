```bash
mkdir -p r3live_ws/src
cd r3live_ws/src
```
# prerequisited
## Livox SDK
```bash
git clone https://github.com/Livox-SDK/Livox-SDK.git
cd Livox-SDK
cd build && cmake ..
make
sudo make install
```
## livox_ros_driver
```bash
cd r3live_ws/src
git clone https://github.com/Livox-SDK/livox_ros_driver.git
catkin_make
```

# r3live
```bash
cd ~/catkin_ws/src
git clone https://github.com/hku-mars/r3live.git
cd ../
catkin_make
source ./devel/setup.bash
```

# run 
```bash
roslaunch r3live r3live_bag.launch
rosbag play YOUR_DOWNLOADED.bag
```