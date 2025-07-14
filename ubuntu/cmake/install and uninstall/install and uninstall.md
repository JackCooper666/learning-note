 Target “cmTC_e7e07“ requires the language dialect “CUDA17“ (with compiler extensions),解决。
 
为了解决 CUDA 17 的编译问题，您需要使用支持 CUDA 17 的 CMake 版本。根据您的问题，您应该至少使用 CMake 3.18 版本，因为该版本增加了对 CUDA 17 的基本支持。不过，建议使用最新的 CMake 版本，以确保获得最新的功能和 bug 修复。

1. **删除旧版本的 CMake（如果有）**：
```bash
sudo apt-get remove --purge cmake
```

2. 访问 CMake 官方网站 下载最新版本的 CMake。或者，您可以使用以下命令下载最新的 CMake 源码包（以 CMake 3.27.0 为例）：