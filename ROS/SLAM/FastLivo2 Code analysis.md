# processImu() for the Forward propagation and motion distortion
Process2()
	inputs: 
		-> LidarMeasures : lidar scanning begin and end time, last lio update time, imu data, img, lio and vio switching flag
		-> \_state: the state estimation from the last frame 
		-> feats\_undistort: raw points cloud in current frame
	main functions:
	

# handleLIO() for the LIO part

# handleVIO() for the VIO part