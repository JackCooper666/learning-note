# Installation
```bash
pip install evo
```
then restart your computer, and run
```bash
evo
```
you will get something like this, this proof that you have installed evo successfully
```bash
usage: evo [-h] {pkg,cat_log} ...

(c) evo authors - license: run 'evo pkg --license'
More docs are available at: github.com/MichaelGrupp/evo/wiki

Python package for the evaluation of odometry and SLAM

Supported trajectory formats:
* TUM trajectory files
* KITTI pose files
* ROS and ROS2 bagfile with geometry_msgs/PoseStamped,
    geometry_msgs/TransformStamped, geometry_msgs/PoseWithCovarianceStamped,
    geometry_msgs/PointStamped, nav_msgs/Odometry topics or TF messages
* EuRoC MAV dataset groundtruth files

The following executables are available:

Metrics:
   evo_ape - absolute pose error
   evo_rpe - relative pose error

Tools:
   evo_traj - tool for analyzing, plotting or exporting multiple trajectories
   evo_res - tool for processing multiple result files from the metrics
   evo_ipython - IPython shell with pre-loaded evo modules
   evo_fig - (experimental) tool for re-opening serialized plots
   evo_config - tool for global settings and config file manipulation

```

if not, please try, and restart your computer
```bash
pip3 install evo
```


# evo_traj
plot one trajectory:
```bash
evo_traj tum/bag/euroc/kitti trajectory.txt/csv
```

# evo_ape
compare two trajectories
```bash
evo_ape  格式  参考轨迹  估计轨迹  [可选项]
#格式：包括kitti、euroc、tum等数据格式
#可选项：有对齐命令、画图、保存结果等
```
此时的终端输出为：  
max：表示最大误差；  
mean：平均误差；  
median：误差中位数；  
min：最小误差；  
rmse：均方根误差；  
sse：和方差、误差平方和；  
std：标准差。

-r  full  ———考虑旋转和平移误差得到的ape,无单位（unit-less）
-r  trans_part  ———考虑平移部分得到的ape，单位为m
-r  rot_part  ———考虑旋转部分得到的ape，无单位（unit-less）
-r  angle_deg  ———考虑旋转角得到的ape,单位°（deg）
-r  angle_rad  ———考虑旋转角得到的ape,单位弧度（rad）
不添加-r和可选项，则默认为trans_part

-v ———详细模式/-verbose mode

-a ———采用SE(3) Umeyama对齐，只处理平移和旋转（轨迹匹配）
-as    ———采用Sim(3) Umeyama对齐，同时处理平移旋转和尺度
-s    ———仅对齐尺度（尺度修正）

不添加-s表示默认尺度对齐参数为1.0，即不进行尺度对齐
![[evo_ape_alignment.png]]
--plot  ———画图  
--plot_mode  xyz———选择三维xyz画图模式，可选参数[xy, xz, yx, yz, zx, zy, xyz]，默认为xyz


 --save_plot ———保存画图结果，后接保存路径
--save_result———存储结果，后接保存路径以及压缩文件名称，存储后得到zip压缩文件


