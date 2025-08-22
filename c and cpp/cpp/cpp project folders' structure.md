# 📌 General Rule
- **`.h` / `.hpp` headers** → go in **`include/`**  
    They contain **declarations** (interfaces) that other parts of the code will include.
- **`.cpp` / `.cu` sources** → go in **`src/`**  
    They contain the **definitions/implementations**, compiled into object files and linked into your executable/library.

```makefile
project/
│── include/
│   └── mylib/
│       ├── my_header.hpp   # class/function declarations
│       └── cuda_kernels.hpp # kernel function declarations
│
└── src/
    ├── main.cpp            # entry point
    ├── cuda_kernels.cu     # kernel implementations
    └── other_code.cpp
```
# 📌 Why?
- `include/` should remain header-only: everything you `#include` into other files.
- `src/` is where you put actual compilation units (`.cpp`, `.cu`), which CMake will build into object files.
- CUDA `.cu` files are **compiled by NVCC**, so they behave more like `.cpp` files than headers.
# 📌 How to wire up in **CMake**
```CMake
project(my_cuda_app LANGUAGES CXX CUDA)

# Add all sources (.cpp and .cu)
add_executable(my_cuda_app
    src/main.cpp
    src/cuda_kernels.cu
)

# Expose include/ for headers
target_include_directories(my_cuda_app PRIVATE include)

# (optional) set CUDA properties
set_target_properties(my_cuda_app PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
    CUDA_STANDARD 14
)

```