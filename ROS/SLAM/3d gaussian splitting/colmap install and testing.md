refer to: CSDN博主「长路可遥」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/weixin_44172157/article/details/122203759

# 1. 安装CUDA 和CUDNN

一定要先安装CUDA和CUDNN，再安装COLMAP，否则在稠密建图时用不了CUDA。

# 2. 安装依赖
```bash
sudo apt-get install openjdk-8-jdk git python-dev python3-dev python-numpy python3-numpy python-six python3-six build-essential python-pip python3-pip python-virtualenv swig python-wheel python3-wheel libcurl3-dev libcupti-dev
```

# 3. get github source core
```bash
git clone https://github.com/colmap/colmap.git

```

# 4. Dependencies from default [Ubuntu](https://so.csdn.net/so/search?q=Ubuntu&spm=1001.2101.3001.7020) repositories
```bash
sudo apt-get install \
    cmake \
    build-essential \
    libboost-all-dev \
    libeigen3-dev \
    libsuitesparse-dev \
    libfreeimage-dev \
    libgoogle-glog-dev \
    libgflags-dev \
    libglew-dev \
    qtbase5-dev \
    libqt5opengl5-dev
```

# 5. Ceres-solver-1.14.0 should be installed
# 6. Compile
```bash
cd path/to/colmap
mkdir build
cd build
cmake ..
make
sudo make install
```
**the version of cmake for the compiling should be larger than 3.27**
otherwise you will get some error like this:
```bash
Target “cmTC_e7e07“ requires the language dialect “CUDA17“ (with compiler extensions),
```
为了解决 CUDA 17 的编译问题，您需要使用支持 CUDA 17 的 CMake 版本。根据您的问题，您应该至少使用 CMake 3.18 版本，因为该版本增加了对 CUDA 17 的基本支持。不过，建议使用最新的 CMake 版本，以确保获得最新的功能和 bug 修复。

# 7. Run COLMAP
```bash
colmap -h
colmap gui
```

