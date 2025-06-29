# camera calibration
## 1. installation
refer to: https://blog.csdn.net/yuku_1111/article/details/136888421?spm=1011.2124.3001.6209

```bash
sudo apt install ros-noetic-camera-calibration
```
## 2. data
rosbag： 
2025-05-07-19-10-49.bag 
2025-05-07-19-53-59.bag
## 3. Start
```bash
#The first terminal 
rosbag play xxx.bag 
# The second terminal 
rosrun camera_calibration cameracalibrator.py --size 8x10 --square 0.02 -- no-service-check image:=/camera/image_color camera:=/camera
```
等数据充⾜后，点击calib.
## 4. Output example

intrinsic 
1205.587536 0.000000 1245.879481 
0.000000 1202.284085 1036.087789 
0.000000 0.000000 1.000000 

distortion 
-0.088614 0.060389 0.000169 0.000279 0.000000

# Lidar2Camera calibration - Livox
## 1. installation
```bash
git clone https://github.com/hku-mars/livox_camera_calib.git
```
## 2. data
2025-05-07-23-08-50.bag - indoor 
2025-05-07-23-28-24.bag - indoor 
2025-05-06-16-58-04.bag - ourdoor 
drive中包含图⽚和点云信息： https://drive.google.com/file/d/1W-gjJNI-cOC0HRikUy-fobDBFOQJy0Jj/view?usp=sharing
## 3. Start
根据livox camera calib的README⾛。 
(本人虽然采⽤的是multi_calib，但测试时把data_num调整为1。) 

最重要的是修改下⾯的文件内容：

1. multi_calib.launch : yaml file调整成⾃⼰的（比如calib_arc.yaml） 
2. calib_arc.yaml : 调整路径&数量（common），调整相机内参，调整yaml路径
	please refer to the camera & lidar内外参标定.pdf
	
3. config_outdoor.yaml : 调整ExtrinsicMat的data为预测的初始内参。后⾯的相机与点云 特征提取参数可以根据情况进⾏调整。比如，让图像对边界更加敏感： Canny.gray_threshold: 10 Canny.len_threshold: 100
## Output 
extrinsic 
-0.00280721 -0.999801 -0.019766 -0.0947847 
-0.0102422   0.0197938 -0.999752 -0.0191468
0.999944      -0.00260407 -0.0102958 -0.0863761 
0                    0                      0            1