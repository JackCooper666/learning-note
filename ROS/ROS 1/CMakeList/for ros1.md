# 1. What is `CMakeLists.txt`?

It’s a build script written in **CMake language**.  
When you run `catkin_make` (or `colcon build`), CMake reads `CMakeLists.txt` to know:
- What dependencies your package needs
- Where to find header files (`.h`)
- Which source files (`.cpp`) to compile
- What libraries/executables to build
- What information to export to other packages

# 2. Structure of a typical ROS `CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.0.2)   # Required CMake version
project(my_pkg)                         # Package name (must match package.xml)

## Find catkin and any catkin packages you depend on
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

## System dependencies (non-catkin, e.g. Eigen, OpenCV)
find_package(Eigen3 REQUIRED)

## Declare the catkin package (export info for other packages)
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES my_lib
  CATKIN_DEPENDS roscpp std_msgs
  DEPENDS Eigen3
)

## Include directories for headers
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
)

## Declare a library
add_library(my_lib
  src/my_lib.cpp
)

## Declare an executable
add_executable(my_node src/my_node.cpp)

## Link libraries to the executable
target_link_libraries(my_node
  my_lib
  ${catkin_LIBRARIES}
  Eigen3::Eigen
)

```

# 3. Explanation of Key Commands
### `cmake_minimum_required(VERSION 3.0.2)`
- Tells CMake the minimum version required.
- Standard in ROS Noetic is `3.0.2`.
### `project(my_pkg)`
- Defines your project/package name.
- Must match your `package.xml` `<name>` tag.
### `find_package(catkin REQUIRED COMPONENTS ...)`
- Loads **catkin** and tells CMake which ROS packages you depend on.
- Example: `roscpp`, `std_msgs`, `sensor_msgs`.
### `find_package(Eigen3 REQUIRED)`
- Finds **non-ROS libraries** installed in your system.
- E.g., Eigen, OpenCV, PCL.
### `catkin_package(...)`
- Declares **what your package exports** to others:
    - `INCLUDE_DIRS`: header files location
    - `LIBRARIES`: libraries built in this package
    - `CATKIN_DEPENDS`: other catkin packages you depend on
    - `DEPENDS`: non-catkin system libraries you depend on
### `include_directories(...)`
- Adds directories for header files (`.h`).
- Common: `include`, `${catkin_INCLUDE_DIRS}`, `${EIGEN3_INCLUDE_DIRS}`.
### `add_library(name src1.cpp src2.cpp)`
- Builds a library from source files.
### `add_executable(name main.cpp)`
- Builds an executable (like a node in ROS).
### `target_link_libraries(target lib1 lib2 ...)`
- Links your executable/library with dependencies.
- Example: link against `catkin_LIBRARIES` or your own `my_lib`.


# 4. How it fits together
Imagine you have this package:
```bash
my_pkg/
 ├── include/my_pkg/my_lib.h
 ├── src/my_lib.cpp
 ├── src/my_node.cpp
 ├── CMakeLists.txt
 └── package.xml
```
- `my_lib.h` (header) goes in `include/`
- `my_lib.cpp` (library code)
- `my_node.cpp` (ROS node that uses the library)
👉 The `CMakeLists.txt` compiles the `.cpp` files into:
- `libmy_lib.so` (library)
- `my_node` (executable node)



# 5. whole pipeline
