# 创建虚拟环境
使用conda创建虚拟环境的命令格式为:
```bash
conda create -n env_name python=3.8
```

# 查看有哪些虚拟环境
```bash
conda env list
conda info -e
conda info --envs
```

# 激活虚拟环境
```bash
conda activate env_name
```

# 退出虚拟环境
```bash
conda activate
conda deactivate
```

# 删除虚拟环境
执行以下命令可以将该指定虚拟环境及其中所安装的包都删除。
```bash
conda remove --name env_name --all
```
如果只删除虚拟环境中的某个或者某些包则是：
```bash
conda remove --name env_name  package_name
```
# 导出环境 
很多的软件依赖特定的环境，我们可以导出环境，这样方便自己在需要时恢复环境，也可以提供给别人用于创建完全相同的环境。
```bash
#获得环境中的所有配置
conda env export --name myenv > myenv.yml
#重新还原环境
conda env create -f  myenv.yml
```

# 包的安装和更新
在当前（虚拟）环境中安装一个包：
```bash
conda install package_name
```
可以用以下命令将某个包更新到它的最新版本 ：
```bash
conda update numpy
```
安装包的时候可以指定从哪个channel进行安装，比如说，以下命令表示不是从缺省通道，而是从conda_forge安装某个包。
```bash
conda install pkg_name -c conda_forge
```

# conda卸载包
```bash
conda uninstall package_name
```
这样会将依赖于这个包的所有其它包也同时卸载。

如果不想删除依赖其当前要删除的包的其他包：
```bash
conda uninstall package_name --force
```

# 清理anaconda缓存
```bash
conda clean -p      # 删除没有用的包 --packages
conda clean -t      # 删除tar打包 --tarballs
conda clean -y -all # 删除所有的安装包及cache(索引缓存、锁定文件、未使用过的包和tar包)
```

# 将版本变更到指定版本
```bash
conda install python=3.5
```
更新完后可以用以下命令查看变更是否符合预期。
```bash
python --version
```

# 将python版本更新到最新版本
如果你想将python版本更新到最新版本，可以使用以下命令：
```bash
conda update python
```