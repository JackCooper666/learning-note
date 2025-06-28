### When to use **CMake**

- Multiple source files and header files
- Use of external libraries (like OpenCV, Boost, Eigen, etc.)
- Need for platform-independent build configuration
- You want to manage build types (Debug/Release)
- Complex compiler/linker settings

---

### ✅ CMake Workflow (Simplified)

1. **Create a CMakeLists.txt** file:
```CMake
cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(my_program main.cpp)
```

2. **Create build directory & run CMake:**    
```bash
mkdir build
cd build
cmake ..
make

```
3. **Run the output:** 
the executable file will be created in the /build folder
```bash
./my_program
```
