refer to: CSDN博主「敢敢のwings」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/lovely_yoshino/article/details/138215540

```cmake
# 设置CMake的最低版本要求
cmake_minimum_required(VERSION 3.15)

# 设置项目名称和版本
project(MyProject VERSION 1.0 DESCRIPTION "An example project with CMake")

# 选项，可以通过-D在命令行定义
option(USE_CUSTOM_LIBRARY "Use a custom library" ON)

# 定义条件预处理器宏
if(USE_CUSTOM_LIBRARY)
    add_definitions(-DUSE_CUSTOM_LIB)
endif()

# 寻找外部依赖包
find_package(Threads REQUIRED)

# 指定头文件的搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)

# 指定库文件搜索路径
link_directories(${PROJECT_SOURCE_DIR}/libs)

# 添加子目录，这些目录下也应该有自己的CMakeLists.txt
add_subdirectory(src)
add_subdirectory(libs)

# 添加一个可执行文件
add_executable(myExecutable src/main.cpp)

# 添加一个静态库
add_library(myStaticLib STATIC src/myStaticLib.cpp)

# 添加一个动态库
add_library(mySharedLib SHARED src/mySharedLib.cpp)

# 设置静态库和动态库的属性
set_target_properties(myStaticLib PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/static_lib"
)
set_target_properties(mySharedLib PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/shared_lib"
    VERSION ${PROJECT_VERSION}
)

# 设置可执行文件的属性
set_target_properties(myExecutable PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    OUTPUT_NAME "myExecutableFinal"
)

# 指定链接库
target_link_libraries(myExecutable PRIVATE myStaticLib mySharedLib Threads::Threads)

# 安装规则
install(TARGETS myExecutable myStaticLib mySharedLib
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib/static
)

# 包含目录
target_include_directories(myExecutable PRIVATE ${PROJECT_SOURCE_DIR}/include)

# 自定义命令和依赖
add_custom_target(run
    COMMAND myExecutable
)
add_dependencies(run myExecutable)

# 宏定义，用于打印消息
macro(print_details)
    message("Project details: ${PROJECT_NAME} version ${PROJECT_VERSION}")
endmacro()
print_details()

# 文件操作示例
file(GLOB_RECURSE MY_SOURCES "src/*.cpp")
target_sources(myExecutable PRIVATE ${MY_SOURCES})

# 配置文件生成
configure_file(config.h.in ${CMAKE_BINARY_DIR}/config.h)

# 源文件目录搜索
aux_source_directory(. DIR_SRCS)
add_executable(myProgram ${DIR_SRCS})

# 添加目录，引入其他项目
add_subdirectory(external)

# 自定义目标，不产生输出文件
add_custom_target(CustomCommand ALL
    COMMAND echo "Executing a custom command"
    COMMENT "This is a custom build step"
)

# 文件复制命令
file(COPY ${CMAKE_SOURCE_DIR}/data.txt DESTINATION ${CMAKE_BINARY_DIR})

```

# 1.1 cmake_minimum_required
制定CMake的最小版本。它确保了 CMake 的特定版本或更高版本的特性能够被利用，并且保证了在旧版本的 CMake 中可能导致未知行为的特性不会被误用。

基本语法：
```cmake
cmake_minimum_required(VERSION major.minor[.patch][.tweak] [FATAL_ERROR])
```
`VERSION` 关键字后面跟着所需的最低版本号。
`FATAL_ERROR` 是一个可选的参数，它在 CMake 的老版本中是必需的，如果用户使用的是比指定的 VERSION 更老的 CMake 版本，CMake 会报告一个致命错误并停止处理。在新版本的 CMake 中，默认情况下，如果版本不满足要求，CMake 就会报错并停止。

# 1.2 project
声明项目的名称和版本，并可选择指定支持的编程语言.此指令通常位于CMakeLists.txt文件的顶部，紧跟在cmake_minimum_required指令之后。

基本语法：

```cmake
project(<PROJECT-NAME> [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
                 [DESCRIPTION <project-description-string>]
                 [HOMEPAGE_URL <url-string>]
                 [LANGUAGES <language-name>...])
```
`<PROJECT-NAME>` 是你的项目名称。
`VERSION` 关键字后面可以跟随项目的版本号。
`DESCRIPTION` 可以添加项目描述。
`HOMEPAGE_URL` 可以指定项目主页的URL。
`LANGUAGES` 关键字后面可以跟一系列编程语言名称，例如 C, CXX (代表C++)，CUDA，Fortran 等。如果不指定语言，CMake默认启用 C 和 CXX。

# 1.3 $
CMake中的美元符号$与括号一起使用，形如 ${...}，用于引用变量的值。最常用的就是和project联系起来，例如：

基本语法：

```cmake
# 设置项目名称和版本
project(MyProject VERSION 1.2.3 LANGUAGES CXX)
set(MY_VARIABLE "Hello, World")

message("Project name: ${PROJECT_NAME}")
message("Project version: ${PROJECT_VERSION}")
message(${MY_VARIABLE})
```

`${MY_VARIABLE}` 会被 CMake 替换为变量 `MY_VARIABLE` 的值.而project 指令将会创建一些变量，比如 `PROJECT_NAME`，`PROJECT_VERSION` 等，这些变量随后可以被引用。

# 1.4 set
在CMake中，set命令用于定义和修改变量。这个命令非常灵活，是CMake脚本中用得最频繁的指令之一，因为它可以用来存储各种类型的数据，如字符串、文件路径、列表（即字符串数组）、布尔值等。

基本语法：

```cmake
set(<variable> <value> [CACHE <type> <docstring> [FORCE]])
```

`<variable>` 是你要设置的变量名。
`<value>` 是分配给变量的值。可以是一个或多个值（如果是多个值，它们会被视为一个列表）。
`CACHE` 选项用于将变量存储到CMake的缓存中，这对于可配置的选项很有用，因为它们在不同的构建中保持不变，除非被用户或者项目脚本修改。
`<type>` 指定缓存中的变量类型，如STRING、BOOL等。
`<docstring>` 是对变量的描述，通常出现在CMake GUI中。
`FORCE` 用于强制覆盖缓存中的值，即使用户已经设置了该值。

在 CMake 中，set 指令用于设置变量的值。它的基本语法如下：

```cmake
set(my_variable "Hello, World!")
```

设置一个列表变量：
```cmake
set(my_list 1 2 3 4 5)
```

设置一个缓存变量：
```cmake
set(my_cached_variable  Release CACHE STRING "Set C++ Compiler Flags" FORCE) # Release or Debug
```

```cmake
# 取消缓存条目
unset(<variable> CACHE)
```

`CMakeCache.txt` 文件用于存储缓存条目，第一次构建时会生成该文件，之后的构建并不会创建该文件。在引用缓存条目时，会去查找该文件，并返回值。

在使用 `set()` 命令时，默认情况下，如果缓存条目在 `CMakeCache.txt` 文件不存在，会创建缓存条目，并写入到 `CMakeCache.txt` 文件中。如果缓存条目在 `CMakeCache.txt` 文件存在，忽略 `set()` 命令，不会覆盖现有的缓存条目。但是我们想强制覆盖现有的缓存条目，我们可以 `FORCE` 选项。

强制设置一个缓存变量：
```cmake
set(my_cached_variable "Another value" CACHE STRING "Description of my_cached_variable" FORCE)
```

以上是 set 指令的基本语法和使用示例，你可以根据具体的需求设置不同类型的变量，如普通变量、列表变量或者缓存变量。

# 1.5 option
在 CMake 中，option 指令用于定义一个布尔类型的选项，这个选项可以用来控制编译过程中的一些行为或特性。基本语法如下：

基本语法：

```cmake
option(<option_variable> "<help_string>" [initial_value])
```

其中：

`<option_variable>` 是要定义的选项的变量名。
`"<help_string>"` 是对选项的描述，会显示在 CMake GUI 或者命令行帮助信息中。
`[initial_value]` 是选项的初始值，可选，默认为 `OFF`。
下面是定义一个开关选项，表示是否启用某个特性：

```cmake
option(ENABLE_FEATURE "Enable some feature" ON)
```

# 1.6 add_definitions
在 CMake 中，add_definitions 指令用于向编译器添加预定义的宏定义。这些宏定义将在编译源文件时起作用。基本语法如下：

```cmake
add_definitions(-D<macro1> [-D<macro2>] ...)
```

其中：

`-D<macro> `表示要定义的宏，`-D` 后跟着宏的名称。如果宏需要带有值，则可以使用等号（`=`）将宏名称与值分隔开。
下面是一些 add_definitions 指令的使用示例：

```cmake
# 定义一个简单的宏：
add_definitions(-DENABLE_LOGGING)

# 定义一个带有值的宏：
add_definitions(-DDEBUG_LEVEL=2)

# 定义多个宏：
add_definitions(-DENABLE_FEATURE_A -DENABLE_FEATURE_B)
```

通过 add_definitions 可以向编译器传递预定义的宏，这些宏在编译源文件时将起到作用。需要注意的是，使用 add_definitions 添加的宏定义将应用于整个项目中的所有源文件。

# 1.7 find_package
在使用 CMake 进行项目开发时，find_package() 是一个非常重要的命令，能够帮助你查找和使用外部库，简化了库的配置和管理工作。假设你正在开发一个项目，突然需要用到一个外部库，比如 Boost、SQLite 或者 OpenCV。手动设置这些库的路径、头文件、库文件的链接，工作量很大，尤其是在跨平台开发时。幸好，CMake 提供了 find_package() 命令，可以自动帮你找到这些库，并且配置好相关路径。

基本语法
```cmake
find_package(<package_name> [version] [EXACT] [QUIET] [MODULE] [REQUIRED]
             [COMPONENTS [components...]]
             [OPTIONAL_COMPONENTS components...]
             [NO_POLICY_SCOPE])
```
参数说明
`<package_name>`: 要查找的软件包的名称。
`version`: 可选参数，用于指定软件包的版本。
`EXACT`: 可选参数，要求找到的软件包的版本必须与指定的版本完全匹配。
`QUIET`: 可选参数，如果找不到软件包不会产生错误消息。
`MODULE`: 可选参数，表示要查找的软件包是一个模块文件而不是一个软件包。
`REQUIRED`: 可选参数，表示找不到软件包时会产生错误消息并停止配置过程。
`COMPONENTS [components...]`: 可选参数，用于指定软件包的组件。
`OPTIONAL_COMPONENTS components...`: 可选参数，用于指定可选的软件包组件。
`NO_POLICY_SCOPE`: 可选参数，指示 CMake 不要修改 CMake 策略。


# 使用例子
查找 Boost 库，要求版本至少是 1.70（版本 >= 1.70）：

```cmake
find_package(Boost 1.70 REQUIRED)
```

这行代码的意思是告诉 CMake，“帮我找一下 Boost 库，至少是版本 1.70，如果找不到就报错”。如果 CMake 成功找到了 Boost，接下来，它会自动设置一些变量，例如：

`Boost_INCLUDE_DIRS`: Boost 的头文件路径
`Boost_LIBRARIES`: Boost 的库文件路径
然后，你可以将这些信息传给 CMake，让它处理编译过程。例如，如果你有一个目标 `my_target`（比如你要编译的可执行文件或库），可以这样告诉 CMake，my_target 需要用到 Boost：

```cmake
# 告诉 CMake，my_target 需要使用 Boost 的头文件
target_include_directories(my_target PRIVATE ${Boost_INCLUDE_DIRS})

# 告诉 CMake，my_target 需要链接 Boost 库
target_link_libraries(my_target PRIVATE ${Boost_LIBRARIES})
```

这段代码的意思是：`target_include_directories()`：把 Boost 的头文件路径加到编译器的搜索路径中，确保编译时能够找到 Boost 的头文件。`target_link_libraries()`：把 Boost 的库文件链接到 `my_target`，确保生成的程序能正确链接到 Boost 库。

查找 OpenSSL 软件包，并要求找到：

```cmake
find_package(OpenSSL REQUIRED)
```
查找 MPI 软件包，并指定 C++ 组件：
```cmake
find_package(MPI REQUIRED COMPONENTS CXX)
```
查找 HDF5 软件包，但是不要求必须找到：

```cmake
find_package(HDF5 QUIET)
if(HDF5_FOUND)
    message(STATUS "HDF5 found: ${HDF5_VERSION}")
else()
    message(STATUS "HDF5 not found")
endif()
```
查找 PythonInterp 软件包，指定版本，如果找不到，打印警告信息：

```cmake
find_package(PythonInterp 3.6 REQUIRED)
if(NOT PythonInterp_FOUND)
    message(WARNING "Python 3.6 or later is required!")
endif()
```
查找 CUDA 软件包，指定版本和特定组件：
```cmake
find_package(CUDA 11.0 REQUIRED COMPONENTS Runtime)
```
**自定义路径依赖库的查找**
在实际开发中，某些库并没有安装在系统默认的路径（比如 /usr/lib 或 /usr/local/lib），导致 `find_package()` 无法找到它们。这时候，就需要告诉 CMake 应该去哪里找这些库。

`find_package()` 的默认查找顺序
- 用户指定的提示路径：如果在 `find_package()` 中使用了 HINTS 或 PATHS 参数，这些路径会被优先考虑。

- 全局配置的路径：CMake 会优先查找全局指定的路径：
	- `CMAKE_PREFIX_PATH`：这是一个全局变量，可以通过命令行或 CMakeLists.txt 配置。
	- 库支持的特定环境变量。例如：Boost 支持 BOOST_ROOT 环境变量。OpenCV 支持 `OpenCV_DIR` 环境变量。

- 库自带的配置文件路径：如果库是使用 CMake 构建的，通常会自带 `<PackageName>Config.cmake` 或 `<lowercasename>-config.cmake` 文件。

- 标准系统路径：如果以上路径都找不到，CMake 会查找系统默认的库路径：

	- Linux：/usr/lib, /usr/local/lib
	- macOS：/opt/local/lib, /usr/local/lib
	- Windows：C:/Program Files/, C:/Program Files (x86)/

如果上述路径中都找不到符合要求的库，CMake 会报错，停止配置过程。

**如何解决**
告诉 CMake 自定义路径即可：

1. 使用 HINTS 或 PATHS 提供路径提示：
```cmake
find_package(MyLib REQUIRED HINTS /custom/path/to/mylib)
```

	 `HINTS` 为 CMake 提供额外的查找路径，优先级高于系统默认路径。
	`PATHS` 用于指定明确的路径，优先级更高。

设置 CMAKE_PREFIX_PATH 变量：

```cmake
set(CMAKE_PREFIX_PATH "/custom/path/to/mylib")
find_package(MyLib REQUIRED)
```
小结
- 使用 find_library() 和 find_path() 可以帮助你找到特定的库文件和头文件，尤其是当库没有提供 Config.cmake 文件时。
- find_library() 用于查找库文件，find_path() 用于查找头文件。


# 1.8 include_directories
include_directories 指令用于向 CMake 项目中添加头文件搜索路径，这样在编译过程中就可以直接使用相对路径或文件名来引用头文件。下面是基本语法和详细使用例子，以 OpenCV 和 Boost 库为例：

基本语法：

```cmake
include_directories([AFTER|BEFORE] [SYSTEM] directory1 [directory2 ...])
```

其中：

AFTER 和 BEFORE 是可选的参数，用于指定添加目录的顺序，默认为 AFTER，即添加到其他包含目录的后面。
SYSTEM 是可选参数，用于标记这些目录中的头文件为系统头文件，编译器可能会忽略其中的警告信息。
directory1, directory2, … 是要添加的头文件搜索路径。
添加 OpenCV 的头文件搜索路径：

```cmake
# 查找 OpenCV 软件包
find_package(OpenCV REQUIRED)

set (INCLUDE_PATH D:\\ProgramFiles\\Qt\\qt5_7_lib_shared_64)
include_directories(${INCLUDE_PATH}/include)       

# 添加外部库的头文件目录
include_directories(/path/to/my_library/include)
# 添加 OpenCV 的头文件搜索路径
include_directories(${OpenCV_INCLUDE_DIRS})
```

在这两个例子中，我们首先使用 find_package 查找了 OpenCV 软件包，并获取了它们的相关信息。然后，通过 include_directories 将它们的头文件搜索路径添加到项目中。这样的设置使得我们可以直接在源代码中使用 OpenCV 库提供的功能，而不需要指定完整的路径或文件名。

find_package 是用于在 CMake 项目中查找并配置外部软件包的功能。当你调用 find_package(OpenCV REQUIRED) 时，CMake 会搜索系统中安装的 OpenCV 软件包，并设置相关的变量，包括 OpenCV_INCLUDE_DIRS 和 OpenCV_LIBS。

OpenCV_INCLUDE_DIRS 变量包含了 OpenCV 头文件的搜索路径。
OpenCV_LIBS 变量包含了 OpenCV 库文件的路径和名称。
因此，当你在 CMakeLists.txt 中使用 ${OpenCV_INCLUDE_DIRS} 时，实际上是在告诉 CMake 去寻找 OpenCV 头文件的位置，这样编译器在编译源代码时就能够找到相应的头文件。

# 1.9 link_libraries
link_libraries 指令用于将库链接到目标文件中。这个指令已经在 CMake 3.13 版本中被标记为不推荐使用，而推荐使用 target_link_libraries 指令。但是，我会提供 link_libraries 的基本语法和一个简单的使用例子。

基本语法：

```cmake
link_libraries(library1 [library2 ...])
```
其中：

library1, library2, … 是要链接的库的名称。
详细使用例子：

```cmake
# 链接某个库到可执行文件中
link_libraries(my_library)
```

在这个例子中，我们使用 `link_libraries` 指令将一个名为 my_library 的库链接到可执行文件中。虽然 `link_libraries` 指令可以完成这个任务，但是它的使用方式相对较简单，而且不够灵活。因此，建议使用更现代的 `target_link_libraries` 指令来替代它，特别是在大型项目中。

- link_libraries 表示添加第三方 lib 库文件的搜索路径。若工程在编译的时候会需要用到某个第三方库的 lib 文件，此时就可以使用 link_libraries

- target_link_libraries 子工程需要用到哪个lib库文件，需要使用 target_link_libraries 指定。（该lib库文件必须能在搜索路径中找到）
# 1.10 target_link_libraries
`target_link_libraries` 指令用于将目标文件（例如可执行文件、库文件）链接到一个或多个库。这是 CMake 中推荐使用的方式。下面是基本语法和详细使用例子：

基本语法：
```cmake
target_link_libraries(target_name library1 [library2 ...])
```
其中：

target_name 是目标文件的名称，可以是可执行文件、库文件等。
library1, library2, … 是要链接到目标文件的库的名称。
基础用法
```cmake
# 添加源文件
add_executable(my_program main.cpp)

# 查找并链接外部库（以 OpenCV 为例）
find_package(OpenCV REQUIRED)
target_link_libraries(my_program ${OpenCV_LIBS})
```

在这个例子中，我们首先使用 add_executable 添加了一个名为 my_program 的可执行文件。然后，我们使用 find_package 查找并配置了 OpenCV 软件包，并获取了它的相关信息。最后，我们使用 target_link_libraries 将 OpenCV 库链接到 my_program 可执行文件中。

target_link_libraries 指令用于将目标与一个或多个库进行链接，这可以是静态库、动态库或可执行文件。

基本语法：

```cmake
target_link_libraries(target_name
    item1
    item2
    ...
)
```
target_name：目标名称，可以是可执行文件、静态库或动态库。
item1, item2, …：要链接的库的名称，可以是库的名称、路径或变量。

链接静态库：
```cmake
# 假设有一个名为 my_library 的静态库
add_library(my_library STATIC ${LIBRARY_SOURCES})

# 将可执行文件 my_executable 与静态库 my_library 进行链接
target_link_libraries(my_executable my_library)
```


链接动态库：
```cmake
# 假设有一个名为 my_dynamic_library 的动态库
add_library(my_dynamic_library SHARED ${DYNAMIC_LIBRARY_SOURCES})

# 将可执行文件 my_executable 与动态库 my_dynamic_library 进行链接
target_link_libraries(my_executable my_dynamic_library)
```

链接静态库和动态库：
```cmake
# 将可执行文件 my_executable 既与静态库 my_library 链接，又与动态库 my_dynamic_library 链接
target_link_libraries(my_executable my_library my_dynamic_library)
```
在以上示例中，target_link_libraries 指令将指定的目标（my_executable）与给定的库（my_library、my_dynamic_library）进行链接。这使得目标可以访问库中定义的函数和变量。

需要注意的是，在链接动态库时，还需要确保动态库在运行时可以被正确找到，可以通过设置LD_LIBRARY_PATH 等环境变量或者在运行时将动态库放置到合适的路径下。

```cmake
export LD_LIBRARY_PATH=/mnt/xxx/usr/lib/
```
# 1.11 include
include 指令用于在 CMake 脚本中包含其他 CMake 脚本文件，以便在当前脚本中使用被包含文件中定义的变量、函数和命令。

基本语法：
```cmake
include(filename)
```
filename：要包含的文件路径。可以是相对路径或绝对路径。
使用示例：
假设你的项目结构如下：

```bash
project/
│
├── CMakeLists.txt
└── cmake/
    └── protobuf-generate.cmake
```
你想在主项目的 `CMakeLists.txt` 中包含 `protobuf-generate.cmake` 文件，你可以这样做：

```cmake
# project/CMakeLists.txt

cmake_minimum_required(VERSION 3.0)
project(MyProject)

# 包含其他 CMake 脚本文件
include(cmake/protobuf-generate.cmake)

# 其他项目配置和构建逻辑
```

然后，在被包含的 cmake/protobuf-generate.cmake 文件中，你可以定义你的生成逻辑：

```cmake
# project/cmake/protobuf-generate.cmake

# 定义生成逻辑
# 在这里可以定义变量、函数、添加目标等

# 例如，定义一个变量
set(PROTOBUF_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/file1.proto
    ${CMAKE_CURRENT_SOURCE_DIR}/protobuf/file2.proto
)

# 例如，添加一个自定义命令和目标来生成 protobuf 文件
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/generated_protobuf_files.cpp
    COMMAND protoc ${PROTOBUF_FILES} --cpp_out=${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${PROTOBUF_FILES}
    COMMENT "Generating Protobuf files"
)

add_custom_target(generate_protobuf_files
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/generated_protobuf_files.cpp
)
```
通过 include 指令，你可以在主项目的 CMakeLists 文件中包含其他的 CMake 脚本文件，使得你的项目结构更加清晰，同时也可以重用已有的代码逻辑。

# 1.12 add_executable
`add_executable` 指令用于创建一个可执行文件目标，它将源文件编译成一个可执行文件。下面是基本语法和详细使用例子：

基本语法：

```cmake
add_executable(target_name source1 [source2 ...])
```

其中：

target_name 是可执行文件的名称。
source1, source2, … 是要编译成可执行文件的源文件。
详细使用例子：

假设我们有一个简单的项目，其中包含两个源文件 main.cpp 和 functions.cpp，我们希望将它们编译成一个可执行文件。

```cmake
# 添加可执行文件目标
add_executable(my_program main.cpp functions.cpp)
```

# 1.13 add_library
add_library 指令用于向 CMake 项目中添加一个新的库（静态库、动态库或模块库）。

基本语法：
```cmake
add_library(<lib_name> [STATIC | SHARED | MODULE | OBJECT]
            [EXCLUDE_FROM_ALL]
            source1.cpp source2.cpp ...)
```
`<lib_name>`：库的名称。
`STATIC`：生成静态库（默认）。
`SHARED`：生成动态库。
`MODULE`：生成模块库。
`OBJECT`：生成对象库。
`EXCLUDE_FROM_ALL`：表示该库不会被默认构建目标所依赖。

使用示例：
```cmake
# 添加源文件
set(SOURCES source1.cpp source2.cpp)

# 生成静态库
add_library(my_static_lib STATIC ${SOURCES})

# 生成动态库
add_library(my_dynamic_lib SHARED ${SOURCES})

# 生成模块库
add_library(my_module_lib MODULE ${SOURCES})

# 生成对象库
add_library(my_object_lib OBJECT ${SOURCES})
```
在以上示例中，分别使用 add_library 指令生成了静态库 my_static_lib、动态库 my_dynamic_lib、模块库 my_module_lib 和对象库 my_object_lib，并指定了对应的源文件列表。

这些库的类型由可选的参数确定，默认为 STATIC，即生成静态库。如果需要生成动态库、模块库或对象库，只需在指令中相应地指定类型即可。

# 1.14 target_include_directories
target_include_directories 指令用于向特定目标添加包含目录，以便在编译时能够找到头文件。

基本语法：
```cmake
target_include_directories(target_name [SYSTEM] [BEFORE]
                           PRIVATE|PUBLIC|INTERFACE
                           [items1...]
                           [items2...]
                           ...)
```

`target_name`：要添加包含目录的目标名称。
`SYSTEM`：可选参数，指定包含的目录是否视为系统头文件目录。
`BEFORE`：可选参数，指定将包含目录添加到目标的头文件搜索路径的开头。
`PRIVATE|PUBLIC|INTERFACE`：指定包含目录的作用范围。
`items1, items2, …`：要添加的包含目录，可以是目录路径、变量、生成器表达式等。
使用示例：
假设你有一个名为 my_library 的库目标，你希望将 include 目录添加到该目标的包含路径中。

```cmake
target_include_directories(my_library PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
```
在这个示例中，my_library 是目标名称，PUBLIC 表示包含路径将被添加到 my_library 的公共接口中，以便其他目标可以访问。${CMAKE_CURRENT_SOURCE_DIR}/include 是要添加的包含目录路径。

你也可以添加多个目录：

```cmake
target_include_directories(my_library PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${SOME_OTHER_DIR}/include
)
```
在这个示例中，除了 ${CMAKE_CURRENT_SOURCE_DIR}/include 外，还将 ${SOME_OTHER_DIR}/include 添加到 my_library 的公共接口中。这个target_include_directories存在传递性，如果打了一个library，然后其他exe文件调用了这个library，使用target_include_directories的PUBLIC可以获取对应的include路径

# 1.15 install
install 指令用于将构建生成的文件（可执行文件、库文件、头文件等）安装到指定的位置。这个指令可以用来将你的软件安装到系统中，使得其他用户可以方便地使用你的软件。

基本语法：
```cmake
install(TARGETS target_name
        [EXPORT <export-name>]
        [ARCHIVE|LIBRARY|RUNTIME|OBJECTS|FRAMEWORK|BUNDLE|DESTINATION <dir>]
        [PERMISSIONS permissions...]
        [CONFIGURATIONS [Debug|Release|...]]
        [COMPONENT <component>]
        [OPTIONAL]
        [INCLUDES DESTINATION [<dir> ...]]
)

install(FILES files...
        [DESTINATION <dir>]
        [PERMISSIONS permissions...]
        [CONFIGURATIONS [Debug|Release|...]]
        [COMPONENT <component>]
        [OPTIONAL]
)

install(DIRECTORY dirs...
        [DESTINATION <dir>]
        [FILE_PERMISSIONS permissions...]
        [DIRECTORY_PERMISSIONS permissions...]
        [USE_SOURCE_PERMISSIONS]
        [CONFIGURATIONS [Debug|Release|...]]
        [COMPONENT <component>]
        [OPTIONAL]
)

install(EXPORT <export-name>
        DESTINATION <dir>
        [NAMESPACE <namespace>]
        [FILE <filename>]
)
```
`TARGETS`：安装目标，可以是可执行文件、库文件等。

这个选项用于指定要安装的目标，可以是通过 `add_executable`、`add_library` 或 `add_custom_target` 创建的目标。它告诉 `CMake` 要安装哪些构建目标。

`EXPORT <export-name>`：将目标导出到其他项目，以便其他项目可以引用这些目标。
	`ARCHIVE`：指定安装目标为静态库归档文件（.a 文件）。
	`LIBRARY`：指定安装目标为共享库文件（动态库，.so 文件）。
	`RUNTIME`：指定安装目标为可执行文件。
	`OBJECTS`：指定安装目标为对象库文件（.o 文件）。
	`FRAMEWORK`：指定安装目标为 macOS 下的框架文件。
	`BUNDLE`：指定安装目标为 macOS 下的捆绑包文件。
	`DESTINATION <dir>`：指定安装目标的目标路径。
`PERMISSIONS permissions...`：指定安装目标的权限。
`CONFIGURATIONS [Debug|Release|...]`：指定只在指定构建配置下安装目标。
`COMPONENT <component>`：指定安装目标的组件。
`OPTIONAL`：指定安装目标是否为可选。
`INCLUDES DESTINATION [<dir> ...]`：指定安装目标的头文件。

`FILES`：要安装的文件列表。

这个选项用于指定要安装的文件列表。你可以列出要安装的每个文件，然后通过 `install(FILES ...) `将它们安装到指定位置。
	`DESTINATION <dir>`：指定安装的目标路径。
	`PERMISSIONS permissions...`：指定安装文件的权限。
	`CONFIGURATIONS [Debug|Release|...]`：指定只在指定构建配置下安装文件。
	`COMPONENT <component>`：指定安装文件的组件。
	`OPTIONAL`：指定安装文件是否为可选。

`DIRECTORY`：要安装的目录列表。
这个选项用于指定要安装的目录列表。它会递归地复制目录中的所有文件和子目录。
	`DESTINATION <dir>`：指定安装的目标路径。
	`FILE_PERMISSIONS permissions...`：指定安装文件的权限。
	`DIRECTORY_PERMISSIONS permissions...`：指定安装目录的权限。
	`USE_SOURCE_PERMISSIONS`：使用源文件的权限。
	`CONFIGURATIONS [Debug|Release|...]`：指定只在指定构建配置下安装目录。
	`COMPONENT <component>`：指定安装目录的组件。
	`OPTIONAL`：指定安装目录是否为可选。

`EXPORT`：将目标导出到其他项目中使用。

这个选项用于将目标导出到其他项目中使用，以便其他项目可以引用这些目标。
	`DESTINATION <dir>`：指定导出的目标路径。
	`NAMESPACE <namespace>`：指定导出的命名空间。
	`FILE <filename>`：指定导出的文件名。

使用示例：

安装可执行文件：
```cmake
install(TARGETS my_executable DESTINATION bin)
```

安装库文`件：
```cmake
install(TARGETS my_library DESTINATION lib)
```

安装头文件：
```cmake
install(FILES my_header.h DESTINATION include)
```

安装整个目录：
```cmake
install(DIRECTORY my_directory DESTINATION share/my_project)
```

导出目标：
```cmake
install(EXPORT my_targets DESTINATION lib/my_project)
```

这些示例分别演示了如何安装可执行文件、库文件、头文件、整个目录以及如何导出目标到其他项目。


# 2. Cmake变量

