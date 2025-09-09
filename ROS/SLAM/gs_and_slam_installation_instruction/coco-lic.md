# prerequisites
- ROS（tested with noetic）
- Eigen 3.3.7（comes with ROS）
- Ceres 2.0.0
- OpenCV 4（comes with ROS）
- PCL >= 1.13
- [livox_ros_driver](https://github.com/Livox-SDK/livox_ros_driver)
- yaml-cpp

use the `roscore` to check the ros version

use the bash command to check the version of the Eigen
```bash
pkg-config --modversion eigen3
```

use the bash command to check the version of the Ceres
```bash
dpkg -L libceres-dev | grep -E 'CeresConfig.cmake|CMake'
# 典型路径（20.04）：
# /usr/lib/x86_64-linux-gnu/cmake/Ceres/CeresConfig.cmake
```

check the pcl version
```bash
apt search libpcl-dev
```
## install the Ceres
### install the dependencies
```bash
sudo apt-get install  liblapack-dev libsuitesparse-dev libcxsparse3 libgflags-dev libgoogle-glog-dev libgtest-dev
```
#### error
```bash
sudo apt-get install liblapack-dev libsuitesparse-dev libcxsparse3 libgflags-dev libgoogle-glog-dev libgtest-dev 
Reading package lists... 
Done Building dependency tree Reading state information... 
Done Package libgoogle-glog-dev is not available, but is referred to by another package. 
This may mean that the package is missing, has been obsoleted, or is only available from another source Package libgflags-dev is not available, but is referred to by another package. This may mean that the package is missing, has been obsoleted, or is only available from another source sh: 0: getcwd() failed: No such file or directory 

E: Package 'libgflags-dev' has no installation candidate 
E: Package 'libgoogle-glog-dev' has no installation candidate
```
solution:
```bash
sudo apt update
sudo apt install -y software-properties-common
sudo add-apt-repository -y universe
sudo apt update
```

### install the Ceres
1. method one
```bash
sudo apt-get install libceres-dev
```
2. method two
```bash
#1. 下载ceres2.0版本
# 地址为 http://ceres-solver.org/ceres-solver-2.0.0.tar.gz
#2. 解压
#3. 进入目录，然后编译
cd ceres-solver
mkdir build && cd build 
cmake ..
make -j3
sudo make install
```
## install abseil
```bash
git clone https://github.com/abseil/abseil-cpp.git
```
进入 abseil-cpp 目录并创建 build 目录：
```bash
cd abseil-cpp
mkdir build
cd build
```
使用 CMake 构建并安装 absl：
```bash
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
make -j
sudo make install
```


## install vtk 7.1.1
get the vtk 7.1.1 by the path https://vtk.org/files/release/7.1/VTK-7.1.1.zip
```bash
cd VTK-7.1.1
mkdir build && cd build
#先配置下qt的版本改成5 再依次点击Configure Generate
cmake-gui
cmake ..
make -j4
sudo make install
```

## install pcl 1.13.1
Go to this https://github.com/PointCloudLibrary/pcl.git github webpage, then switch the branch to pcl-1.13.1
```bash
git clone https://github.com/PointCloudLibrary/pcl.git
```

```bash
cd pcl-pcl-1.13.1 
mkdir build && cd build 
cmake .. \
  -DCMAKE_BUILD_TYPE=None \
  -DCMAKE_INSTALL_PREFIX=/usr/local \
  -DCMAKE_PREFIX_PATH=/usr/lib/x86_64-linux-gnu \
  -DFREETYPE_LIBRARY=/usr/lib/x86_64-linux-gnu/libfreetype.so \
  -DBUILD_GPU=ON \
  -DBUILD_apps=ON \
  -DBUILD_simulation=ON \
  -DBUILD_tools=OFF \
  -DBUILD_examples=OFF \
  -DBUILD_apps=OFF \
  -DBUILD_visualization=OFF \
  -DWITH_VTK=OFF \
  -DWITH_QT=OFF \
  -DWITH_OPENGL=OFF \
  -DWITH_OPENMP=ON \
  -DWITH_QHULL=ON \
  -DWITH_EIGEN=ON -DWITH_FLANN=ON \
  -DCMAKE_CXX_STANDARD=17 \
  -DCMAKE_CXX_FLAGS_RELEASE="-O2"

# 一般这步容易出错
make -j6
#make install指令pcl项目文件 转到默认的路径/usr/include 下
sudo make install
```


# install coco-lic
```bash
mkdir -p ~/catkin_coco/src
cd ~/catkin_coco/src
git clone https://github.com/Livox-SDK/livox_ros_driver.git
cd ~/catkin_coco && catkin_make
cd ~/catkin_coco/src
git clone https://github.com/APRIL-ZJU/Coco-LIC.git
cd ~/catkin_coco && catkin_make

cd ~/catkin_coco/src/Coco-LIC && mkdir data
```
