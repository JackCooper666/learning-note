# Prerequisited

## PCL && Eigen && OpenCV
PCL>=1.8, Follow [PCL Installation](https://pointclouds.org/).
Eigen>=3.3.4, Follow [Eigen Installation](https://eigen.tuxfamily.org/index.php?title=Main_Page).
OpenCV>=4.2, Follow [Opencv Installation](http://opencv.org/).
check the version of them
```bash
:~$ pkg-config --modversion pcl_common
1.13.1
:~$ pkg-config --modversion eigen3
3.3.7
:~$ python3 -c "import cv2; print(cv2.__version__)"
4.2.0
```
## Sophus
please refer to /ROS/SLAM/thirdparty_install

## Vikit
```bash
# Different from the one used in fast-livo1
cd catkin_ws/src
git clone https://github.com/xuankuzcr/rpg_vikit.git 
```


# build
```bash
cd ~/catkin_ws/src
git clone https://github.com/hku-mars/FAST-LIVO2
cd ../
catkin_make
source ~/catkin_ws/devel/setup.bash
```