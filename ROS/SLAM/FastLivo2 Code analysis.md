# processImu() for the Forward propagation and motion distortion
Process2()
	main functions:
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
				-> 

# handleLIO() for the LIO part

# handleVIO() for the VIO part