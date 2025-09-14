# 1. `package.xml` vs `CMakeLists.txt`

| File               | Purpose                                                                                                  |
| ------------------ | -------------------------------------------------------------------------------------------------------- |
| **package.xml**    | Metadata: tells ROS _what this package is_, what it depends on, who maintains it, version, license, etc. |
| **CMakeLists.txt** | Build instructions: tells CMake _how to compile_ your code, link libraries, export dependencies.         |
- `package.xml` = _declaration_ (what you need & provide)
- `CMakeLists.txt` = _implementation_ (how to build it)
# 2. Example: Dependencies
Suppose you use `roscpp`, `std_msgs`, and `Eigen3`.
### In `package.xml`

```xml
<package format="2">
  <name>my_pkg</name>
  <version>0.0.1</version>
  <description>A demo package</description>
  <maintainer email="you@todo.com">Your Name</maintainer>
  <license>BSD</license>

  <!-- Build dependencies -->
  <build_depend>roscpp</build_depend>
  <build_depend>std_msgs</build_depend>
  <build_depend>eigen</build_depend>

  <!-- Run dependencies -->
  <exec_depend>roscpp</exec_depend>
  <exec_depend>std_msgs</exec_depend>
  <exec_depend>eigen</exec_depend>
</package>

```
### In `CMakeLists.txt`
```cmake
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

find_package(Eigen3 REQUIRED)

catkin_package(
  CATKIN_DEPENDS roscpp std_msgs
  DEPENDS Eigen3
)
```

# 3. The handshake
- **Step 1**: When you run `catkin_make`, catkin first **reads `package.xml`** to check dependencies are installed.
- **Step 2**: Then it **runs `CMakeLists.txt`** to configure how to compile.
- **Step 3**: During `catkin_package(...)`, it uses info from both files to generate export files (so other packages that depend on yours can build correctly).
So:
- `package.xml` = what’s required
- `CMakeLists.txt` = how to use those requirements in compilation