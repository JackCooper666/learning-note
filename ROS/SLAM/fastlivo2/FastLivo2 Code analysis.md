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

### the lio point cloud result in world frame based on the lio state estimation:
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
	->`LidarMeasures.measures.back().img`: the img in current frame
	->`_pv_list` : the downsampled point cloud
	->`voxelmap_manager->voxel_map_`
	->`LidarMeasures.last_lio_update_time - _first_lidar_time` 

## main functions:
`updateFrameState(*state);`
`retrieveFromVisualSparseMap(img, pg, feat_map);`
`computeJacobianAndUpdateEKF(img);`
`generateVisualMapPoints(img, pg);`
`plotTrackedPoints();`
`updateVisualMapPoints(img);`
`updateReferencePatch(feat_map);`



# the point cloud update pipeline
1. feat_undistort: is the points cloud after the forward propagation and motion undistortion
2. feat_down_body: the down-sampled point cloud of feat_undistort  
3. feat_down_world: the IMU predication state after the forward propagation, this state translate the feat_down_body from the IMU frame to the world frame
4. feat_down_world -> LIO StateEstimation() -> `_state = voxelmap_manager->state_ //estimated state` 
5. `_pv_list = voxelmap_manage->pv_list_` : the IMU predication state after the forward propagation, this state translate the feat_down_body from the IMU frame to the world frame.
6. `world_lidar`  -> `transformLidar(_state.rot_end, _state.pos_end, feats_down_body, world_lidar);`
7. `voxelmap_manager->pv_list_` gets the points cloud in the frame from the `world_lidar` by the following code.
```cpp
for (size_t i = 0; i < world_lidar->points.size(); i++)
{
voxelmap_manager->pv_list_[i].point_w << world_lidar->points[i].x, world_lidar->points[i].y, world_lidar->points[i].z;

M3D point_crossmat = voxelmap_manager->cross_mat_list_[i];

M3D var = voxelmap_manager->body_cov_list_[i];

var = (_state.rot_end * extR) * var * (_state.rot_end * extR).transpose() +

(-point_crossmat) * _state.cov.block<3, 3>(0, 0) * (-point_crossmat).transpose() + _state.cov.block<3, 3>(3, 3);

voxelmap_manager->pv_list_[i].var = var;
}
voxelmap_manager->UpdateVoxelMap(voxelmap_manager->pv_list_);

```
8. `_pv_list = voxelmap_manager->pv_list_;`
9.  `laserCloudFullRes` get the `feats_undistort` or the `feats_down_body` according to user setting
10. `laserCloudWorld`: `RGBpointBodyToWorld(&laserCloudFullRes->points[i], &laserCloudWorld->points[i]);` transforms the `laserCloudFullRes` from IMU frame to world frame.
11. `*pcl_w_wait_pub = *laserCloudWorld;`: if the VIO is enabled, the `pcl_w_wait_pub` will be put into the VIO, else the `pcl_w_wait_pub` will be published. 
12. `vio_manager->processFrame(LidarMeasures.measures.back().img, _pv_list, voxelmap_manager->voxel_map_, LidarMeasures.last_lio_update_time - _first_lidar_time);` the `_pv_list` will transfer into the vio state estimation system


# key variables
## `SubSparseMap *visual_submap; // 当前帧patch地图`

```cpp
struct SubSparseMap

{

vector<float> propa_errors;

vector<float> errors;

vector<vector<float>> warp_patch;

vector<int> search_levels;

vector<VisualPoint *> voxel_points;

vector<double> inv_expo_list;

vector<pointWithVar> add_from_voxel_map;

  

SubSparseMap()

{

propa_errors.reserve(SIZE_LARGE);

errors.reserve(SIZE_LARGE);

warp_patch.reserve(SIZE_LARGE);

search_levels.reserve(SIZE_LARGE);

voxel_points.reserve(SIZE_LARGE);

inv_expo_list.reserve(SIZE_LARGE);

add_from_voxel_map.reserve(SIZE_SMALL);

};

  

void reset()

{

propa_errors.clear();

errors.clear();

warp_patch.clear();

search_levels.clear();

voxel_points.clear();

inv_expo_list.clear();

add_from_voxel_map.clear();

}

};

/// A visual map point on the surface of the scene.

class VisualPoint : boost::noncopyable

{

public:

EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  

Vector3d pos_; //!< 3d pos of the point in the world coordinate frame.

Vector3d normal_; //!< Surface normal at point.

Matrix3d normal_information_; //!< Inverse covariance matrix of normal estimation.

Vector3d previous_normal_; //!< Last updated normal vector.

list<Feature *> obs_; //!< Reference patches which observe the point.

Eigen::Matrix3d covariance_; //!< Covariance of the point.

bool is_converged_; //!< True if the point is converged.

bool is_normal_initialized_; //!< True if the normal is initialized.

bool has_ref_patch_; //!< True if the point has a reference patch.

Feature *ref_patch; //!< Reference patch of the point.

  

// added by zewen for the Jacobian computation

float weight_{1.}; // 视觉点权重

float weight_2_{1.}; // 深度调权

float weight_3_{1.}; // source畸变权重

float weight_4_{1.}; // target畸变权重

  
  
  

VisualPoint(const Vector3d &pos);

~VisualPoint();

void findMinScoreFeature(const Vector3d &framepos, Feature *&ftr) const;

void deleteNonRefPatchFeatures();

void deleteFeatureRef(Feature *ftr);

void addFrameRef(Feature *ftr);

bool getCloseViewObs(const Vector3d &pos, Feature *&obs, const Vector2d &cur_px) const;

};
```

## 📌 Meaning of `curvature`
In the context of the `PointXYZINormal` structure, the `**curvature**` field represents the **surface curvature** at a 3D point in a point cloud, typically calculated from the local neighborhood of the point.

- `curvature` is a **scalar value** that quantifies **how flat or curved** the local surface is around the point.
- It is commonly derived during **normal estimation** using **Principal Component Analysis (PCA)** on neighboring points.