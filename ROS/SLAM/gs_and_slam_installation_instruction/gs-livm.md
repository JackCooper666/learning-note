# prerequisites
cuda = 11.8

# install mamba
please refer to ubuntu/conda/install/mamba install

# create mamba env
```conda
mamba create -n {ENV_NAME} python=3.9
mamba activate {ENV_NAME}
```

# install ROS in current mamba
```conda
mamba install ros-noetic-desktop-full -c RoboStack
```

# install the cmake, make, gcc, g++ and sophus in mamba
check the path of the cmake, make, gc, g++
```bash
which cmake
which make
which gcc
which g++
gcc --version
g++ --version
```


```conda
mamba install cxx-compiler=1.5.0
mamba install make
mamba install conda-forge::sophus
mamba install conda-forge::tsl_robin_map
mamba install -y -c conda-forge libgomp 
```

# build Livox-SDK and livox_ros_driver2 in mamba

```bash
# download
mkdir -p ~/catkin_ws/src && cd ~/catkin_ws/src

git clone https://github.com/Livox-SDK/Livox-SDK2
cd Livox-SDK2 && mkdir build && cd build

# cmake options, -DCMAKE_INSTALL_PREFIX is path of your conda environment
cmake -DCMAKE_INSTALL_PREFIX=/home/xieys/miniforge3/envs/{ENV_NAME}  ..

# make && make install
make -j60 && make install

#clone livox_ros_driver2 and put it in your catkin_ws/src. If you don not use Livox, you can skip this step by changing -DBUILD_LIVOX=OFF in CMakeLists.txt
cd ~/catkin_ws/src
git clone https://github.com/Livox-SDK/livox_ros_driver2

cd livox_ros_driver2

(Important)(****NOTE, the source code have boon changed in livox_ros_driver2/CMakeLists.txt to support build. Please refer to the following one)

./build.sh ROS1
```
## CMakelist.txt in livox_ros_driver2
```CMakeList
# # judge which cmake codes to use

# if(ROS_EDITION STREQUAL "ROS1")

  

# Copyright(c) 2019 livoxtech limited.

  

cmake_minimum_required(VERSION 3.0)

  
  

#---------------------------------------------------------------------------------------

# Start livox_ros_driver2 project

#---------------------------------------------------------------------------------------

include(cmake/version.cmake)

project(livox_ros_driver2 VERSION ${LIVOX_ROS_DRIVER2_VERSION} LANGUAGES CXX)

message(STATUS "livox_ros_driver2 version: ${LIVOX_ROS_DRIVER2_VERSION}")

  

#---------------------------------------------------------------------------------------

# Add ROS Version MACRO

#---------------------------------------------------------------------------------------

add_definitions(-DBUILDING_ROS1)

  

#---------------------------------------------------------------------------------------

# find package and the dependecy

#---------------------------------------------------------------------------------------

find_package(Boost 1.54 REQUIRED COMPONENTS

system

thread

chrono

)

  

## Find catkin macros and libraries

## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)

## is used, also find other catkin packages

find_package(catkin REQUIRED COMPONENTS

roscpp

rospy

sensor_msgs

std_msgs

message_generation

rosbag

pcl_ros

)

  

## Find pcl lib

find_package(PCL REQUIRED)

  

## Generate messages in the 'msg' folder

add_message_files(FILES

CustomPoint.msg

CustomMsg.msg

# Message2.msg

)

  

## Generate added messages and services with any dependencies listed here

generate_messages(DEPENDENCIES

std_msgs

)

  

find_package(PkgConfig)

pkg_check_modules(APR apr-1)

if (APR_FOUND)

message(${APR_INCLUDE_DIRS})

message(${APR_LIBRARIES})

endif (APR_FOUND)

  

###################################

## catkin specific configuration ##

###################################

## The catkin_package macro generates cmake config files for your package

## Declare things to be passed to dependent projects

## INCLUDE_DIRS: uncomment this if your package contains header files

## LIBRARIES: libraries you create in this project that dependent projects als o need

## CATKIN_DEPENDS: catkin_packages dependent projects also need

## DEPENDS: system dependencies of this project that dependent projects also n eed

catkin_package(CATKIN_DEPENDS

roscpp rospy std_msgs message_runtime

pcl_ros

)

  

#---------------------------------------------------------------------------------------

# Set default build to release

#---------------------------------------------------------------------------------------

if(NOT CMAKE_BUILD_TYPE)

set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)

endif()

  

#---------------------------------------------------------------------------------------

# Compiler config

#---------------------------------------------------------------------------------------

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)

  

## make sure the livox_lidar_sdk_static library is installed

find_library(LIVOX_LIDAR_SDK_LIBRARY liblivox_lidar_sdk_static.a /usr/local/lib)

  

## PCL library

link_directories(${PCL_LIBRARY_DIRS})

add_definitions(${PCL_DEFINITIONS})

  

#---------------------------------------------------------------------------------------

# generate excutable and add libraries

#---------------------------------------------------------------------------------------

add_executable(${PROJECT_NAME}_node

""

)

  

#---------------------------------------------------------------------------------------

# precompile macro and compile option

#---------------------------------------------------------------------------------------

target_compile_options(${PROJECT_NAME}_node

PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>

)

  

#---------------------------------------------------------------------------------------

# add projects that depend on

#---------------------------------------------------------------------------------------

add_dependencies(${PROJECT_NAME}_node ${PROJECT_NAME}_generate_messages_cpp)

  

#---------------------------------------------------------------------------------------

# source file

#---------------------------------------------------------------------------------------

target_sources(${PROJECT_NAME}_node

PRIVATE

src/driver_node.cpp

src/lds.cpp

src/lds_lidar.cpp

src/lddc.cpp

src/livox_ros_driver2.cpp

  

src/comm/comm.cpp

src/comm/ldq.cpp

src/comm/semaphore.cpp

src/comm/lidar_imu_data_queue.cpp

src/comm/cache_index.cpp

src/comm/pub_handler.cpp

  

src/parse_cfg_file/parse_cfg_file.cpp

src/parse_cfg_file/parse_livox_lidar_cfg.cpp

  

src/call_back/lidar_common_callback.cpp

src/call_back/livox_lidar_callback.cpp

)

  

#---------------------------------------------------------------------------------------

# include file

#---------------------------------------------------------------------------------------

target_include_directories(${PROJECT_NAME}_node

PUBLIC

${catkin_INCLUDE_DIRS}

${PCL_INCLUDE_DIRS}

${APR_INCLUDE_DIRS}

3rdparty

src

)

  

#---------------------------------------------------------------------------------------

# link libraries

#---------------------------------------------------------------------------------------

target_link_libraries(${PROJECT_NAME}_node

${LIVOX_LIDAR_SDK_LIBRARY}

${Boost_LIBRARY}

${catkin_LIBRARIES}

${PCL_LIBRARIES}

${APR_LIBRARIES}

)

  
  

#---------------------------------------------------------------------------------------

# Install

#---------------------------------------------------------------------------------------

  

install(TARGETS ${PROJECT_NAME}_node

ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}

LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}

RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}

)

  

install(DIRECTORY launch_ROS1/

DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}/launch_ROS1

)

  

#---------------------------------------------------------------------------------------

# end of CMakeList.txt

#---------------------------------------------------------------------------------------

  
  

# else(ROS_EDITION STREQUAL "ROS2")

  

# # Copyright(c) 2020 livoxtech limited.

  

# cmake_minimum_required(VERSION 3.14)

# project(livox_ros_driver2)

  

# # Default to C99

# if(NOT CMAKE_C_STANDARD)

# set(CMAKE_C_STANDARD 99)

# endif()

  

# # Default to C++14

# if(NOT CMAKE_CXX_STANDARD)

# set(CMAKE_CXX_STANDARD 14)

# endif()

  

# list(INSERT CMAKE_MODULE_PATH 0 "${PROJECT_SOURCE_DIR}/cmake/modules")

  

# if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")

# add_compile_options(-Wall -Wextra -Wpedantic -Wno-unused-parameter)

# endif()

  

# # Printf version info

# include(cmake/version.cmake)

# project(${PROJECT_NAME} VERSION ${LIVOX_ROS_DRIVER2_VERSION} LANGUAGES CXX)

# message(STATUS "${PROJECT_NAME} version: ${LIVOX_ROS_DRIVER2_VERSION}")

  

# #---------------------------------------------------------------------------------------

# # Add ROS Version MACRO

# #---------------------------------------------------------------------------------------

# add_definitions(-DBUILDING_ROS2)

  

# # find dependencies

# # uncomment the following section in order to fill in

# # further dependencies manually.

# # find_package(<dependency> REQUIRED)

# find_package(ament_cmake_auto REQUIRED)

# ament_auto_find_build_dependencies()

# find_package(PCL REQUIRED)

# find_package(std_msgs REQUIRED)

# find_package(builtin_interfaces REQUIRED)

# find_package(rosidl_default_generators REQUIRED)

  

# # check apr

# find_package(PkgConfig)

# pkg_check_modules(APR apr-1)

# if (APR_FOUND)

# message(${APR_INCLUDE_DIRS})

# message(${APR_LIBRARIES})

# endif (APR_FOUND)

  

# # generate custom msg headers

# set(LIVOX_INTERFACES livox_interfaces2)

# rosidl_generate_interfaces(${LIVOX_INTERFACES}

# "msg/CustomPoint.msg"

# "msg/CustomMsg.msg"

# DEPENDENCIES builtin_interfaces std_msgs

# LIBRARY_NAME ${PROJECT_NAME}

# )

  

# ## make sure the livox_lidar_sdk_shared library is installed

# find_library(LIVOX_LIDAR_SDK_LIBRARY liblivox_lidar_sdk_shared.so /usr/local/lib REQUIRED)

  

# ##

# find_path(LIVOX_LIDAR_SDK_INCLUDE_DIR

# NAMES "livox_lidar_api.h" "livox_lidar_def.h"

# REQUIRED)

  

# ## PCL library

# link_directories(${PCL_LIBRARY_DIRS})

# add_definitions(${PCL_DEFINITIONS})

  

# # livox ros2 driver target

# ament_auto_add_library(${PROJECT_NAME} SHARED

# src/livox_ros_driver2.cpp

# src/lddc.cpp

# src/driver_node.cpp

# src/lds.cpp

# src/lds_lidar.cpp

  

# src/comm/comm.cpp

# src/comm/ldq.cpp

# src/comm/semaphore.cpp

# src/comm/lidar_imu_data_queue.cpp

# src/comm/cache_index.cpp

# src/comm/pub_handler.cpp

  

# src/parse_cfg_file/parse_cfg_file.cpp

# src/parse_cfg_file/parse_livox_lidar_cfg.cpp

  

# src/call_back/lidar_common_callback.cpp

# src/call_back/livox_lidar_callback.cpp

# )

  

# target_include_directories(${PROJECT_NAME} PRIVATE ${livox_sdk_INCLUDE_DIRS})

  

# # get include directories of custom msg headers

# if(HUMBLE_ROS STREQUAL "humble")

# rosidl_get_typesupport_target(cpp_typesupport_target

# ${LIVOX_INTERFACES} "rosidl_typesupport_cpp")

# target_link_libraries(${PROJECT_NAME} "${cpp_typesupport_target}")

# else()

# set(LIVOX_INTERFACE_TARGET "${LIVOX_INTERFACES}__rosidl_typesupport_cpp")

# add_dependencies(${PROJECT_NAME} ${LIVOX_INTERFACES})

# get_target_property(LIVOX_INTERFACES_INCLUDE_DIRECTORIES ${LIVOX_INTERFACE_TARGET} INTERFACE_INCLUDE_DIRECTORIES)

# endif()

  

# # include file direcotry

# target_include_directories(${PROJECT_NAME} PUBLIC

# ${PCL_INCLUDE_DIRS}

# ${APR_INCLUDE_DIRS}

# ${LIVOX_LIDAR_SDK_INCLUDE_DIR}

# ${LIVOX_INTERFACES_INCLUDE_DIRECTORIES} # for custom msgs

# 3rdparty

# src

# )

  

# # link libraries

# target_link_libraries(${PROJECT_NAME}

# ${LIVOX_LIDAR_SDK_LIBRARY}

# ${LIVOX_INTERFACE_TARGET} # for custom msgs

# ${PPT_LIBRARY}

# ${Boost_LIBRARY}

# ${PCL_LIBRARIES}

# ${APR_LIBRARIES}

# )

  

# rclcpp_components_register_node(${PROJECT_NAME}

# PLUGIN "livox_ros::DriverNode"

# EXECUTABLE ${PROJECT_NAME}_node

# )

  

# if(BUILD_TESTING)

# find_package(ament_lint_auto REQUIRED)

# # the following line skips the linter which checks for copyrights

# # uncomment the line when a copyright and license is not present in all source files

# #set(ament_cmake_copyright_FOUND TRUE)

# # the following line skips cpplint (only works in a git repo)

# # uncomment the line when this package is not in a git repo

# #set(ament_cmake_cpplint_FOUND TRUE)

# ament_lint_auto_find_test_dependencies()

# endif()

  

# ament_auto_package(INSTALL_TO_SHARE

# config

# launch_ROS2

# )

  

# endif()
```

# install torch
```conda
conda install pytorch=2.0.1 -c pytorch -c nvidia -c conda-forge
conda install -c pytorch -c nvidia pytorch=2.0.1 pytorch-cuda=11.8
```
## check the installation of the torch
```python
python - <<'PY'
import sys, platform, inspect
import torch, torch.backends.cudnn as cudnn

print("Python:", sys.version.split()[0], "| OS:", platform.platform())
print("Torch:", torch.__version__, "| CUDA (built):", torch.version.cuda)
print("cuDNN available:", cudnn.is_available(), "| version:", cudnn.version())

print("CUDA available (runtime):", torch.cuda.is_available())
if torch.cuda.is_available():
    print("GPU count:", torch.cuda.device_count())
    for i in range(torch.cuda.device_count()):
        print(f"  [{i}] {torch.cuda.get_device_name(i)} | CC:", torch.cuda.get_device_capability(i))
    # 简单算一把，确保真正在 GPU 上跑
    x = torch.randn(2048, 2048, device='cuda')
    y = x @ x.T
    torch.cuda.synchronize()
    print("GPU matmul OK, mean =", y.mean().item())
else:
    print("CPU-only build或当前看不到GPU（可能在登录节点或没申请到GPU资源）。")

print("Torch path:", inspect.getfile(torch))
PY

```
## error
undefined symbol: iJIT_NotifyEvent, **MKL 版本过新（≥2024.1）** 与 **conda 版 PyTorch 2.0.1** 的动态链接不兼容导致的：`iJIT_NotifyEvent` 在新版 MKL 里不再导出，而 `libtorch_cpu.so` 仍在找它。
```conda
conda install -y -c conda-forge --override-channels \
  "mkl==2024.0.0" "libblas=*=*mkl" "libcblas=*=*mkl" "liblapack=*=*mkl" "liblapacke=*=*mkl"
```

# install GS-LIVM

```bash
mkdir -p ~/catkin_ws/src && cd ~/catkin_ws/src

# clone
git clone https://github.com/xieyuser/GS-LIVM.git
```

```conda
# install other packages
cd GS-LIVM
conda install --file conda_pkgs.txt -c nvidia -c pytorch -c conda-forge
```
this is the new conda_pkg.txt, the original one is wrong, the cuda 12.1 is not compatible with pytorch 2.0.1
```txt
# ---------------- Core / ABI ----------------
python=3.9

# BLAS backend  ——  修复 libtorch_cpu.so 的 MKL 符号问题
mkl==2024.0.0
mkl-include==2024.0.0
mkl-devel==2024.0.0
libblas=*=*mkl
libcblas=*=*mkl
liblapack=*=*mkl
liblapacke=*=*mkl

# ---------------- PyTorch (CUDA 11.8) ----------------
pytorch==2.0.1
pytorch-cuda==11.8
torchvision==0.15.2
torchaudio==2.0.2
# 可选：CUDA 编译器（与 cu118 匹配；用于编译 simple-knn / diff_gaussian_rasterization 等）
cuda-nvcc=11.8.*

# ---------------- Build Toolchain ----------------
cxx-compiler==1.5.0
cmake>=3.24
ninja
eigen>=3.3.4

# ---------------- Geometry / C++ libs ----------------
# conda-forge 上 2.0.0 不一定总有，用区间避免冲突（2.2.x 可）
ceres-solver>=2.0.0,<2.3
tsl_robin_map>=1.3.0
libcnpy

# ---------------- ROS 工具（如需） ----------------
catkin_tools
catkin_pkg
empy
rospkg
vcstool
```
# build GS-LIVM
```bash
# build
cd ~/catkin_ws
catkin build   # change some DEFINITIONS

# source
# (either) temporary
source ~/catkin_ws/devel/setup.bash

# (or) start with conda activate
echo "ROS_FILE=/home/xieys/catkin_ws/devel/setup.bash
if [ -f \"\$ROS_FILE\" ]; then
    echo \$ROS_FILE
    source \$ROS_FILE
fi" >> ~/miniforge3/envs/{ENV_NAME}/setup.sh
```

the CMakeList.txt, package.xml and package_livox.xml in the GS-LIVM were wrong, please use the following one
## error
### cuda_runtime.h missing
```conda
mamba install -y -c conda-forge cuda-cudart-dev
```
### cannot find the livox_ros_driver2
change the catkin_package to this one
```CMakelist
catkin_package(
  CATKIN_DEPENDS geometry_msgs nav_msgs roscpp rospy std_msgs sensor_msgs tf pcl_ros cv_bridge livox_ros_driver2 eigen_conversions
  DEPENDS EIGEN3
)
```
add the following lines in the package.xml
```xml
<build_depend>livox_ros_driver2</build_depend>
<build_export_depend>livox_ros_driver2</build_export_depend>
<exec_depend>livox_ros_driver2</exec_depend>
```
### could not find OpenMP
```conda
mamba install conda-forge::openmp
```
change the `find_package(OpenMP REQUIRED COMPONENTS C CXX)` to
```cmake
find_package(OpenMP REQUIRED COMPONENTS CXX)
```
### cv_bridge is not in the package.xml
put the following three lines in the package.xml
```xml
<build_depend>cv_bridge</build_depend>
<build_export_depend>cv_bridge</build_export_depend>
<exec_depend>cv_bridge</exec_depend>
```
### `pthread_*_clock*` 未定义 —— 工具链/头文件混搭导致

这是因为你当前环境 **同时** 用到了：
- **Conda 的 sysroot**（`sysroot_linux-64=2.17`），提供的是 **老版本 glibc 2.17** 的头文件；
- **系统的 GCC 11 的 libstdc++ 头文件**（`/usr/include/c++/11`），这些头里会调用较新的 `pthread_*_clock*` 接口（需要较新的 glibc）。
```bash
# 1) 清理一下之前的配置/缓存
catkin clean -y

# 2) 确保使用的是conda里的编译器
export CC=$(which gcc)         # 显示为 .../envs/gslivm/bin/gcc 10.4
export CXX=$(which g++)
export CUDAHOSTCXX=$(which g++)

# 3) 覆盖 catkin 的 CMake 参数（把你原来写死的 /usr/bin/g++-11 去掉）
catkin config --cmake-args \
  -DCMAKE_CUDA_HOST_COMPILER="$(which g++)" \
  -DCUDA_PROPAGATE_HOST_FLAGS=OFF \
  -DCMAKE_CUDA_STANDARD=17 -DCMAKE_CXX_STANDARD=17 \
  -DCMAKE_CUDA_ARCHITECTURES=86 \
  -DTorch_DIR="$CONDA_PREFIX/lib/python3.9/site-packages/torch/share/cmake/Torch" \
  '-DCMAKE_CUDA_FLAGS=--std=c++17 --expt-relaxed-constexpr -Xcompiler=-fno-tree-vectorize -Xcompiler=-fno-strict-aliasing'

# 4) 重建
catkin build gslivm
```

### **`c10::guts::to_string`** undefined

**PyTorch 2.4 删除了 `c10::guts::to_string`**，导致 `src/gs/gaussian.cu` 里 6 处调用报错。

在 `gaussian.cu` 顶部**加入头文件**（放在任何 `#include <torch...>` 之上或之下都行）
```cpp
#include <c10/util/string_utils.h>
```
把所有 `c10::guts::to_string` **替换为** `c10::str`




```bash
export CC=$(which gcc)
export CXX=$(which g++)
export CUDAHOSTCXX=$(which g++)
export PCL_DIR="$CONDA_PREFIX/share/pcl-1.12"

catkin config --cmake-args \
  -DCMAKE_CUDA_HOST_COMPILER="$(which g++)" \
  -DCUDA_PROPAGATE_HOST_FLAGS=OFF \
  -DCMAKE_CUDA_STANDARD=17 -DCMAKE_CXX_STANDARD=17 \
  -DCMAKE_CUDA_ARCHITECTURES=86 \
  -DTorch_DIR="$CONDA_PREFIX/lib/python3.9/site-packages/torch/share/cmake/Torch" \
  '-DCMAKE_CUDA_FLAGS=--std=c++17 --expt-relaxed-constexpr -Xcompiler=-fno-tree-vectorize -Xcompiler=-fno-strict-aliasing'



```




%% ## CMakeList
```CMakeList
cmake_minimum_required(VERSION 3.2)

option(BUILD_GS "option for build 3DGS" ON)

if(BUILD_GS)
  if(NOT DEFINED CMAKE_CUDA_ARCHITECTURES)
    set(CMAKE_CUDA_ARCHITECTURES "80;86;90")
  endif()

  project(gslivm LANGUAGES CUDA CXX)
  add_definitions(-DBUILD_GS)
  message(STATUS "will build gaussian")
else()
  project(gslivm LANGUAGES CXX)
endif()

set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_definitions(-O3)

if(BUILD_GS)
  set(CMAKE_CUDA_STANDARD 17)
  set(CMAKE_CUDA_STANDARD_REQUIRED ON)
  set(CMAKE_CUDA_EXTENSIONS OFF)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")

add_definitions(-DROOT_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/\")

option(USE_LIVOX "option for livox" ON)
if(USE_LIVOX)
  set(PACKAGE_XML_PATH ${CMAKE_CURRENT_SOURCE_DIR}/package_livox.xml)
  add_definitions(-DUSE_LIVOX)
  find_package(catkin REQUIRED COMPONENTS
    eigen_conversions
    geometry_msgs
    nav_msgs
    pcl_ros
    roscpp
    rospy
    sensor_msgs
    std_msgs
    tf
    livox_ros_driver2
    cv_bridge
  )
  else()
  set(PACKAGE_XML_PATH ${CMAKE_CURRENT_SOURCE_DIR}/package.xml)
  find_package(catkin REQUIRED COMPONENTS
    eigen_conversions
    geometry_msgs
    nav_msgs
    pcl_ros
    roscpp
    rospy
    sensor_msgs
    std_msgs
    tf
    cv_bridge
  )
endif(USE_LIVOX)

find_package(TBB REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenMP REQUIRED)
find_package(PythonLibs REQUIRED)

find_package(PCL REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(Ceres REQUIRED)
find_package(OpenCV REQUIRED)

find_package(Sophus REQUIRED)
find_package(tsl-robin-map REQUIRED)

if(BUILD_GS)
  find_package(CUDAToolkit REQUIRED)
endif()

if(${OpenMP_CXX_FOUND})
    message(WARNING "OpenMP found and will be used.")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -Xcompiler=${OpenMP_CXX_FLAGS}")
else()
    message(FATAL_ERROR "OpenMP not found")
endif()

catkin_package(
  CATKIN_DEPENDS geometry_msgs nav_msgs sensor_msgs tf roscpp rospy pcl_ros eigen_conversions cv_bridge livox_ros_driver2
  DEPENDS EIGEN3
)

if(BUILD_GS)
  include_directories(include/gs)
endif(BUILD_GS)

include_directories(  
  include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIR}
  ${CERES_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
  ${SOPHUS_INCLUDE_DIR}
  ${OpenCV_INCLUDE_DIRS}
  ${tsl-robin-map_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/external/tinyply/source
  ${PYTHON_INCLUDE_DIRS}
)

include_directories(
  ${CUDAToolkit_INCLUDE_DIRS}
)

# common
add_library(${PROJECT_NAME}.common 
  src/common/timer/timer.cc
)

if(BUILD_GS)
  include("${PROJECT_SOURCE_DIR}/cmake/torch.cmake")

  list(APPEND CMAKE_PREFIX_PATH ${TORCH_CMAKE_PREFIX_PATH}
    $ENV{CMAKE_PREFIX_PATH})
  find_package(Torch REQUIRED)
  add_subdirectory(external)

  set(gs_libs
    ${TORCH_LIBRARIES}
    ${OpenCV_LIBS}
    tinyply
    glm
    CUDA::cudart
    CUDA::curand
    CUDA::cublas
    CUDA::cusolver
    Threads::Threads
    args
    cnpy
  )

  include_directories(${TORCH_INCLUDE_DIRS})

  # gs
  set(SOURCES
    src/gs/gaussian.cu
    src/gs/camera.cu
    src/gs/loss_monitor.cu
    src/gs/parameters.cu
    src/gs/rasterizer.cu
    src/gs/rasterize_points.cu
    src/cuda_rasterizer/backward.cu
    src/cuda_rasterizer/forward.cu
    src/cuda_rasterizer/rasterizer_impl.cu)

  add_library(${PROJECT_NAME}.gs ${SOURCES})
  target_link_libraries(${PROJECT_NAME}.gs ${gs_libs} ${PCL_LIBRARIES} ${sophus_LIBRARIES})
  target_compile_features(${PROJECT_NAME}.gs PRIVATE cxx_std_17)

  # gp3d
  set(
    gp_files
    src/gp3d/cell.cpp
    src/gp3d/map.cpp
    src/gp3d/gpprocess.cu
  )

  add_library(${PROJECT_NAME}.gp3d ${gp_files})
  target_link_libraries(
    ${PROJECT_NAME}.gp3d 
    ${gs_libs}
    ${PCL_LIBRARIES} 
    ${OpenCV_LIBRARIES}
    ${PROJECT_NAME}.common
    OpenMP::OpenMP_CXX
  )
  target_compile_features(${PROJECT_NAME}.gp3d PRIVATE cxx_std_17)
endif(BUILD_GS)

add_executable(livo_node
		src/liw/lioOptimization.cpp
		src/liw/imageProcessing.cpp
		src/liw/opticalFlowTracker.cpp
		src/liw/rgbMapTracker.cpp
		src/liw/lkpyramid.cpp
		src/liw/optimize.cpp
		src/liw/cloudMap.cpp
		src/liw/cloudProcessing.cpp 
		src/liw/state.cpp
		src/liw/eskfEstimator.cpp
		src/liw/utility.cpp
		src/liw/parameters.cpp
    src/liw/cudaMatrixMultiply.cpp)

target_link_libraries(livo_node ${catkin_LIBRARIES} ${PROJECT_NAME}.common ${PROJECT_NAME}.gs ${PROJECT_NAME}.gp3d ${CERES_LIBRARIES} ${OpenCV_LIBRARIES} tsl::robin_map)

# gmm
# find_package(Open3D REQUIRED)  
# include_directories(${Open3D_INCLUDE_DIR} src/test/gmm)

# add_library(${PROJECT_NAME}.gmm src/test/gmm/GMMFit.cpp)
# target_link_libraries(${PROJECT_NAME}.gmm ${gs_libs} Open3D::Open3D)

# add_executable(
#   ${PROJECT_NAME}_test_gmm
#   src/test/test_gmm.cpp
# )
# target_link_libraries(${PROJECT_NAME}_test_gmm  ${PROJECT_NAME}.gmm )

# eclipse
# find_package(Open3D REQUIRED)  
# include_directories(${Open3D_INCLUDE_DIR})

# add_executable(
#   ${PROJECT_NAME}_test_ecli
#   src/test/test_ecli.cpp
# )
# target_link_libraries(${PROJECT_NAME}_test_ecli ${gs_libs} Open3D::Open3D )

# hash
# add_executable(
#   ${PROJECT_NAME}_test_hash
#   src/test/test_hash.cpp
# )

# target_link_libraries(${PROJECT_NAME}_test_hash  pthread)
```

## package.xml
```xml
This XML file does not appear to have any style information associated with it. The document tree is shown below.  

<package format="2">

<name>gslivm</name>

<version>0.0.0</version>

<description>The gslivm package</description>

<!-- One maintainer tag required, multiple allowed, one person per tag -->

<!-- Example: -->

<!-- <maintainer email="jane.doe@example.com">Jane Doe</maintainer> -->

<maintainer email="gslivm@todo.todo">gslivm</maintainer>

<!-- One license tag required, multiple allowed, one license per tag -->

<!-- Commonly used license strings: -->

<!-- BSD, MIT, Boost Software License, GPLv2, GPLv3, LGPLv2.1, LGPLv3 -->

<license>TODO</license>

<!-- Url tags are optional, but multiple are allowed, one per tag -->

<!-- Optional attribute type can be: website, bugtracker, or repository -->

<!-- Example: -->

<!-- <url type="website">http://wiki.ros.org/gslivm</url> -->

<!-- Author tags are optional, multiple are allowed, one per tag -->

<!-- Authors do not have to be maintainers, but could be -->

<!-- Example: -->

<!-- <author email="jane.doe@example.com">Jane Doe</author> -->

<!-- The *depend tags are used to specify dependencies -->

<!-- Dependencies can be catkin packages or system dependencies -->

<!-- Examples: -->

<!-- Use depend as a shortcut for packages that are both build and exec dependencies -->

<!-- <depend>roscpp</depend> -->

<!-- Note that this is equivalent to the following: -->

<!-- <build_depend>roscpp</build_depend> -->

<!-- <exec_depend>roscpp</exec_depend> -->

<!-- Use build_depend for packages you need at compile time: -->

<!-- <build_depend>message_generation</build_depend> -->

<!-- Use build_export_depend for packages you need in order to build against this package: -->

<!-- <build_export_depend>message_generation</build_export_depend> -->

<!-- Use buildtool_depend for build tool packages: -->

<!-- <buildtool_depend>catkin</buildtool_depend> -->

<!-- Use exec_depend for packages you need at runtime: -->

<!-- <exec_depend>message_runtime</exec_depend> -->

<!-- Use test_depend for packages you need only for testing: -->

<!-- <test_depend>gtest</test_depend> -->

<!-- Use doc_depend for packages you need only for building documentation: -->

<!-- <doc_depend>doxygen</doc_depend> -->

<buildtool_depend>catkin</buildtool_depend>

<build_depend>eigen_conversions</build_depend>

<build_depend>geometry_msgs</build_depend>

<build_depend>nav_msgs</build_depend>

<build_depend>pcl_conversions</build_depend>

<build_depend>pcl_ros</build_depend>

<build_depend>roscpp</build_depend>

<build_depend>rospy</build_depend>

<build_depend>sensor_msgs</build_depend>

<build_depend>std_msgs</build_depend>

<build_depend>tf</build_depend>

<build_depend>cv_bridge</build_depend>

<build_depend>livox_ros_driver2</build_depend>

<exec_depend>cv_bridge</exec_depend>

<exec_depend>livox_ros_driver2</exec_depend>

<build_export_depend>eigen_conversions</build_export_depend>

<build_export_depend>geometry_msgs</build_export_depend>

<build_export_depend>nav_msgs</build_export_depend>

<build_export_depend>pcl_conversions</build_export_depend>

<build_export_depend>pcl_ros</build_export_depend>

<build_export_depend>roscpp</build_export_depend>

<build_export_depend>rospy</build_export_depend>

<build_export_depend>sensor_msgs</build_export_depend>

<build_export_depend>std_msgs</build_export_depend>

<build_export_depend>tf</build_export_depend>

<exec_depend>eigen_conversions</exec_depend>

<exec_depend>geometry_msgs</exec_depend>

<exec_depend>nav_msgs</exec_depend>

<exec_depend>pcl_conversions</exec_depend>

<exec_depend>pcl_ros</exec_depend>

<exec_depend>roscpp</exec_depend>

<exec_depend>rospy</exec_depend>

<exec_depend>sensor_msgs</exec_depend>

<exec_depend>std_msgs</exec_depend>

<exec_depend>tf</exec_depend>

<!-- The export tag contains other, unspecified, tags -->

<export>

<!-- Other tools can request additional information be placed here -->

</export>

</package>

```

## package_livox.xml
```xml
<?xml version="1.0"?>

<package format="2">

<name>gslivm</name>

<version>0.0.0</version>

<description>The gslivm package</description>

  

<!-- One maintainer tag required, multiple allowed, one person per tag -->

<!-- Example: -->

<!-- <maintainer email="jane.doe@example.com">Jane Doe</maintainer> -->

<maintainer email="gslivm@todo.todo">gslivm</maintainer>

  
  

<!-- One license tag required, multiple allowed, one license per tag -->

<!-- Commonly used license strings: -->

<!-- BSD, MIT, Boost Software License, GPLv2, GPLv3, LGPLv2.1, LGPLv3 -->

<license>TODO</license>

  

<buildtool_depend>catkin</buildtool_depend>

<build_depend>eigen_conversions</build_depend>

<build_depend>geometry_msgs</build_depend>

<build_depend>nav_msgs</build_depend>

<build_depend>pcl_conversions</build_depend>

<build_depend>pcl_ros</build_depend>

<build_depend>roscpp</build_depend>

<build_depend>rospy</build_depend>

<build_depend>sensor_msgs</build_depend>

<build_depend>std_msgs</build_depend>

<build_depend>tf</build_depend>

<build_export_depend>eigen_conversions</build_export_depend>

<build_export_depend>geometry_msgs</build_export_depend>

<build_export_depend>nav_msgs</build_export_depend>

<build_export_depend>pcl_conversions</build_export_depend>

<build_export_depend>pcl_ros</build_export_depend>

<build_export_depend>roscpp</build_export_depend>

<build_export_depend>rospy</build_export_depend>

<build_export_depend>sensor_msgs</build_export_depend>

<build_export_depend>std_msgs</build_export_depend>

<build_export_depend>tf</build_export_depend>

<build_depend>livox_ros_driver2</build_depend>

<exec_depend>livox_ros_driver2</run_depend>

<exec_depend>eigen_conversions</exec_depend>

<exec_depend>geometry_msgs</exec_depend>

<exec_depend>nav_msgs</exec_depend>

<exec_depend>pcl_conversions</exec_depend>

<exec_depend>pcl_ros</exec_depend>

<exec_depend>roscpp</exec_depend>

<exec_depend>rospy</exec_depend>

<exec_depend>sensor_msgs</exec_depend>

<exec_depend>std_msgs</exec_depend>

<exec_depend>tf</exec_depend>

  
  

<!-- The export tag contains other, unspecified, tags -->

<export>

<!-- Other tools can request additional information be placed here -->

  

</export>

</package>
```



 %%