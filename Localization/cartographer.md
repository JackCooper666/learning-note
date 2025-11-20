# How to use cartographer and cartographer ros in my workspace with navigation.

### 0. 安装

```
cd ~/ME5413_Final_Project/src/me5413_thirdparty
git clone https://github.com/cartographer-project/cartographer.git
git clone https://github.com/cartographer-project/cartographer_ros.git
```


### 1. 首先先单独编译 `cartographer`

```
cd ~/ME5413_Final_Project/src/me5413_thirdparty/cartographer
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
make -j4
sudo make install

```

may got some error



### 2. 在 `me5413_thirdparty/cartographer` 里创建 `CATKIN_IGNORE`

直接创建 `CATKIN_IGNORE` 文件
```
touch ~/ME5413_Final_Project/src/me5413_thirdparty/cartographer/CATKIN_IGNORE
```

### 3. 最后编译整个工作空间
```
cd ~/ME5413_Final_Project
catkin_make
source devel/setup.bash
```


