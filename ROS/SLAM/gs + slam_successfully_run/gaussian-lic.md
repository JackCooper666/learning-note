# prerequisites
- Install [CUDA 11.7](https://developer.nvidia.com/cuda-11-7-1-download-archive?target_os=Linux&target_arch=x86_64&Distribution=Ubuntu&target_version=20.04&target_type=runfile_local) with [cuDNN v8.9.7](https://developer.nvidia.com/rdp/cudnn-archive). please refer to "ubuntu/nvidia/cudnn install and link it with cuda toolkit"
- opencv 4.7.0
- libtorch for cuda 11.7
- gcc 9.4.0 and g++ 9.4.0
- GLM
## install GLM
```bash
sudo apt-get update
sudo apt-get install libglm-dev
```

## install opencv 4.7.0
```bash
mkdir -p ~/Software/opencv
cd ~/Software/opencv
wget https://github.com/opencv/opencv/archive/refs/tags/4.7.0.tar.gz && tar -zxvf 4.7.0.tar.gz && rm -rf 4.7.0.tar.gz
wget https://github.com/opencv/opencv_contrib/archive/refs/tags/4.7.0.tar.gz && tar -zxvf 4.7.0.tar.gz && rm -rf 4.7.0.tar.gz

cd ~/Software/opencv/opencv-4.7.0
mkdir build && cd build
cmake ..\
-D CMAKE_BUILD_TYPE=RELEASE \
-D CMAKE_C_COMPILER=/usr/bin/gcc \
-D CMAKE_CXX_COMPILER=/usr/bin/g++ \
-D CUDA_HOST_COMPILER=/usr/bin/g++ \
-D WITH_CUDA=ON \
-D WITH_CUDNN=ON \
-D OPENCV_DNN_CUDA=ON \
-D WITH_NVCUVID=ON \
-D CUDA_TOOLKIT_ROOT_DIR=/usr/local/cuda \
-D OPENCV_EXTRA_MODULES_PATH="../../opencv_contrib-4.7.0/modules" \
-D BUILD_TIFF=ON \
-D BUILD_ZLIB=ON \
-D BUILD_JASPER=ON \
-D BUILD_CCALIB=ON \
-D BUILD_JPEG=ON \
-D WITH_FFMPEG=ON
make -j$(nproc)
```

## install libtorch cuda 11.7
```bash
cd ~/Software
wget https://download.pytorch.org/libtorch/cu117/libtorch-cxx11-abi-shared-with-deps-2.0.1%2Bcu117.zip
unzip libtorch-cxx11-abi-shared-with-deps-2.0.1+cu117.zip && rm -rf libtorch-cxx11-abi-shared-with-deps-2.0.1+cu117.zip
```
# install coco-lic
please refer to ROS/SLAM/gs+slam_successfully_run/coco-lic

# install gaussian-lic
```bash
mkdir -p ~/catkin_gaussian/src
cd ~/catkin_gaussian/src
git clone https://github.com/APRIL-ZJU/Gaussian-LIC.git
cd ~/catkin_gaussian && catkin_make
```