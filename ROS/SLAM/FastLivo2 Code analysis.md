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
output:
	-> voxelmap_manager->state_: estimated state
	->voxelmap_manager->pv_list_: downsampled points cloud
	-> voxelmap_manager->ptpl_list_: a list of **point-to-plane residuals** (and associated geometric information) that are **built from** the downsampled point cloud (`pv_list_`).

### the lio point cloud reslu in world frame based on the lio state estimation:
`the *pul_w_wait_pub` is the point cloud result and will be pushed into the vio system

```cpp
PointCloudXYZI::Ptr laserCloudFullRes(dense_map_en ? feats_undistort : feats_down_body);
int size = laserCloudFullRes->points.size();
PointCloudXYZI::Ptr laserCloudWorld(new PointCloudXYZI(size, 1));

for (int i = 0; i < size; i++)
{
	RGBpointBodyToWorld(&laserCloudFullRes->points[i], &laserCloudWorld->points[i]);
}
*pcl_w_wait_pub = *laserCloudWorld;

void LIVMapper::RGBpointBodyToWorld(PointType const *const pi, PointType *const po)

{
V3D p_body(pi->x, pi->y, pi->z);
V3D p_global(_state.rot_end * (extR * p_body + extT) + _state.pos_end);
po->x = p_global(0);
po->y = p_global(1);
po->z = p_global(2);
po->intensity = pi->intensity;
}
```

# handleVIO() for the VIO part

the state estimation in the vio part is in the `vio_manager->processFrame`
inputs:
	->

