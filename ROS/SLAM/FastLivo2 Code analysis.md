slam_mode_ = (img_en && lidar_en) ? LIVO : imu_en ? ONLY_LIO : ONLY_LO;
# sync_packages()
proposes: for **synchronizing sensor data** (LiDAR, IMU, and optionally camera images) into a coherent `LidarMeasureGroup meas` structure, **based on SLAM mode and timing constraints**.
VIO:
- Waits for a camera frame.
- Associates IMU data up to that image's timestamp.
LIO:
Finds LiDAR frames whose timestamp is **before the image capture time**.
# processImu() for the Forward propagation and motion undistortion
## Process2()
### main functions:
-> IMU_init(): to calculate the gravity, acceleration and angular velocity, then initialise the bias and state.
	inputs: 
	-> LidarMeasures : lidar scanning begin and end time, last lio update time, imu data, img, lio and vio switching flag
	-> \_state: the state estimation from the last frame 
	-> feats\_undistort: raw points cloud in current frame
->UndistortPcl(): to do the Forward propagation and motion distortion. 
	inputs: 
		-> LidarMeasures : lidar scanning begin and end time, last lio update time, imu data, img, lio and vio switching flag
		-> \_state: the state estimation from the last frame 
		-> feats\_undistort: raw points cloud in current frame
	outputs:
		-> \_state: the results after forward propagation and motion distortion

# handleLIO() for the LIO part
## main functions
### downSizeFilterSurf.setInputCloud(feats_undistort); downSizeFilterSurf.filter(\*feats_down_body);
to get the down sampled points cloud (\*feat_down_body)
### voxelmap_manager->StateEstimation(state_propagat);
LIO ESIKF state estimation
inputs:
	-> state_propagat: the state after forward propagation and motion undistortion

# handleVIO() for the VIO part