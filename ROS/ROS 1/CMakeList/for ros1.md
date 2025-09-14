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
## 1. The Big Picture: How `catkin_make` runs
When you run:
```bash
catkin_make
```
it actually runs in **two phases**:
1. **Configure Phase**
    - CMake reads your `CMakeLists.txt` **line by line**.
    - Commands like `project()`, `find_package()`, `include_directories()`, `catkin_package()`, `add_executable()` are parsed.
    - It **does not compile code yet** — it just generates **build files** (e.g., Makefiles or Ninja build rules).
2. **Build Phase**
    - Then `make` (or ninja) is called.
    - It uses the build rules generated in the configure phase.
    - `add_executable` and `add_library` targets get compiled.
    - Linking happens.

## 2. Execution Order in `CMakeLists.txt`
A typical ROS `CMakeLists.txt` runs like this:
(a) CMake setup
```cmake
cmake_minimum_required(VERSION 3.0.2)
project(my_pkg)
```
- CMake initializes the project.
- Defines variables like `PROJECT_NAME`, `PROJECT_SOURCE_DIR`

(b) Find dependencies
```cmake
find_package(catkin REQUIRED COMPONENTS roscpp std_msgs)
find_package(Eigen3 REQUIRED)
```
- At configure time, CMake looks for installed packages.
- If missing, configuration **fails immediately**.
- Each `find_package` usually sets variables (e.g. `EIGEN3_INCLUDE_DIRS`, `catkin_INCLUDE_DIRS`).

(c) Declare catkin_package
```cmake
catkin_package(
  INCLUDE_DIRS include
  LIBRARIES my_lib
  CATKIN_DEPENDS roscpp std_msgs
  DEPENDS Eigen3
)
```
- Still configure time.
- This **does not build** anything.
- It generates `my_pkgConfig.cmake` files inside `devel/` or `install/`.
- These files are later used when another package does `find_package(my_pkg)`.


(d) Set include directories
```cmake
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
)
```
- At configure time, this **adds paths to a list**.
- Later, when you call `add_executable` or `add_library`, these paths are injected into the compiler call like:
```cpp
g++ -I/home/user/catkin_ws/src/my_pkg/include -I/opt/ros/noetic/include ...
```
- So **no file is included yet** — it only defines compiler search paths.

(e) Define libraries and executables
```cmake
add_library(my_lib src/my_lib.cpp)
add_executable(my_node src/my_node.cpp)
```
- At configure time: registers a new **target** (`my_lib`, `my_node`).
- Each target is like a build rule in Make.
- Nothing is compiled yet — just a rule like:
    > “To build `my_node`, compile `src/my_node.cpp` with these include paths and link with these libraries.”

(f) Link libraries
```cmake
target_link_libraries(my_node
  my_lib
  ${catkin_LIBRARIES}
  Eigen3::Eigen
)
```
- At configure time: attaches dependencies to the target.
- At build time: `g++` is called with `-lmy_lib -lroscpp -lEigen...`.

# 3. Build Phase (make)
Once CMake has generated all rules, you run:
```bash
make -j8
```

Now:
1. For each target (`my_node`, `my_lib`):
    - Compiler commands are run, e.g.:
```bash
g++ -Iinclude -I/opt/ros/noetic/include -I/usr/include/eigen3 -c src/my_node.cpp -o CMakeFiles/my_node.dir/src/my_node.cpp.o
```
    - `include_directories` values appear as `-I` flags here.
2. After all `.o` object files are built, they get linked:
```bash
g++ CMakeFiles/my_node.dir/src/my_node.cpp.o -o devel/lib/my_pkg/my_node -lroscpp -lstd_msgs -lmy_lib
```
2. Results (executables and libraries) are written into `devel/lib/my_pkg/`.