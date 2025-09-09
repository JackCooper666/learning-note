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

1.5 option
在 CMake 中，option 指令用于定义一个布尔类型的选项，这个选项可以用来控制编译过程中的一些行为或特性。基本语法如下：

基本语法：

option(<option_variable> "<help_string>" [initial_value])
AI写代码
cmake
1
其中：

<option_variable> 是要定义的选项的变量名。
"<help_string>" 是对选项的描述，会显示在 CMake GUI 或者命令行帮助信息中。
[initial_value] 是选项的初始值，可选，默认为 OFF。
下面是定义一个开关选项，表示是否启用某个特性：

option(ENABLE_FEATURE "Enable some feature" ON)
AI写代码
cmake
1
1.6 add_definitions
在 CMake 中，add_definitions 指令用于向编译器添加预定义的宏定义。这些宏定义将在编译源文件时起作用。基本语法如下：

add_definitions(-D<macro1> [-D<macro2>] ...)
AI写代码
cmake
1
其中：

-D<macro> 表示要定义的宏，-D 后跟着宏的名称。如果宏需要带有值，则可以使用等号（=）将宏名称与值分隔开。
下面是一些 add_definitions 指令的使用示例：

定义一个简单的宏：
add_definitions(-DENABLE_LOGGING)
AI写代码
cmake
1
定义一个带有值的宏：
add_definitions(-DDEBUG_LEVEL=2)
AI写代码
cmake
1
定义多个宏：
add_definitions(-DENABLE_FEATURE_A -DENABLE_FEATURE_B)
AI写代码
cmake
1
通过 add_definitions 可以向编译器传递预定义的宏，这些宏在编译源文件时将起到作用。需要注意的是，使用 add_definitions 添加的宏定义将应用于整个项目中的所有源文件。

1.7 find_package
在使用 CMake 进行项目开发时，find_package() 是一个非常重要的命令，能够帮助你查找和使用外部库，简化了库的配置和管理工作。假设你正在开发一个项目，突然需要用到一个外部库，比如 Boost、SQLite 或者 OpenCV。手动设置这些库的路径、头文件、库文件的链接，工作量很大，尤其是在跨平台开发时。幸好，CMake 提供了 find_package() 命令，可以自动帮你找到这些库，并且配置好相关路径。

基本语法
find_package(<package_name> [version] [EXACT] [QUIET] [MODULE] [REQUIRED]
             [COMPONENTS [components...]]
             [OPTIONAL_COMPONENTS components...]
             [NO_POLICY_SCOPE])
AI写代码
cmake
1
2
3
4
参数说明
<package_name>: 要查找的软件包的名称。
version: 可选参数，用于指定软件包的版本。
EXACT: 可选参数，要求找到的软件包的版本必须与指定的版本完全匹配。
QUIET: 可选参数，如果找不到软件包不会产生错误消息。
MODULE: 可选参数，表示要查找的软件包是一个模块文件而不是一个软件包。
REQUIRED: 可选参数，表示找不到软件包时会产生错误消息并停止配置过程。
COMPONENTS [components...]: 可选参数，用于指定软件包的组件。
OPTIONAL_COMPONENTS components...: 可选参数，用于指定可选的软件包组件。
NO_POLICY_SCOPE: 可选参数，指示 CMake 不要修改 CMake 策略。
————————————————
版权声明：本文为CSDN博主「敢敢のwings」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/lovely_yoshino/article/details/138215540