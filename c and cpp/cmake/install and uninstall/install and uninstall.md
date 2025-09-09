 Target “cmTC_e7e07“ requires the language dialect “CUDA17“ (with compiler extensions),解决。
 
为了解决 CUDA 17 的编译问题，您需要使用支持 CUDA 17 的 CMake 版本。根据您的问题，您应该至少使用 CMake 3.18 版本，因为该版本增加了对 CUDA 17 的基本支持。不过，建议使用最新的 CMake 版本，以确保获得最新的功能和 bug 修复。

**此安装方法使用软连接**

1. **删除旧版本的 CMake（如果需要删除原CMake）**：
```bash
sudo apt-get remove --purge cmake
```

2. 访问 CMake 官方网站 下载最新版本的 CMake。或者，您可以使用以下命令下载最新的 CMake 源码包（以 CMake 3.27.0 为例）：
```bash
wget https://github.com/Kitware/CMake/releases/download/v3.27.1/cmake-3.27.1.tar.gz
tar -zxvf cmake-3.27.1.tar.gz
```
紧接着你把解压出来的[安装包](https://so.csdn.net/so/search?q=%E5%AE%89%E8%A3%85%E5%8C%85&spm=1001.2101.3001.7020)移动到/opt目录下，用这行代码
```bash
sudo mv /home/yangyouze/Downloads/cmake-3.27.0 /opt/cmake-3.27.0
```
然后安装
```bash
cd /opt/cmake-3.27.0
./bootstrap
make
sudo make install
```
3. **删除原有的软链接标记（很重要）**
```bash
sudo rm /usr/local/bin/cmake
```
4. **创建cmake的软链接**
```bash
sudo ln -s /opt/cmake-3.27.0/bin/cmake /usr/local/bin/cmake
```
5. **查看版本就好**
```bash
cmake --version
```
