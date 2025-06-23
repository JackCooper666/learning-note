

# Points cloud transformation pipeline
LIO system
1. `PredicteStateAndUndistortCloud(LidarMeasures,state,feats_undistort)`前向传播+反向传播去畸变, input is `feat_undistort`, output is `feat_undistort`
2. `feat_undistort` -> `PreprocessCloud(feat_undistort)` this function will filter the tailing points and far points, then downsample the filtered points to get the `feats_down_body`
3. `feat_down_world`: the `feat_down_body`use the states estimation results from the IMU forward propagation to get the `feat_down_world` in `BuildKdTree(feats_down_body);` -> `pointBodyToWorld(&(feats_down_body->points[i]),&(feats_down_world->points[i]));`

EstimateLIOState()
 4.  each point in the `feat_down_world` will be checked, and the points who cannot fit a surface with their neighbours will be filter out. `laserCloudOri->points[effct_feat_num] = feats_down_body->points[i];` and the effect points will be put into the `laserCloudOri`.
 5. `lidar_selector->lidar_feat_num = effct_feat_num;`
 6. `laserCloudOri` will be used in the ICP and IEKF 

PublishLIOResult()
7. `feat_down_body` -> `cloud_registered_I`
8. `cloud_registered_I` -> `RGBpointBodyToWorld(&cloud_registered_I->points[i],&cloud_registered_W->points[i]);` -> `cloud_registered_W`
9. `cloud_registered_W`->`pcl::copyPointCloud(*cloud_registered_W,*valid_source_indices,*valid_source_cloud);` -> `valid_source_cloud`



VIO system
EstimateVIOState()
1. `const auto &valid_source_cloud_for_VIO = valid_source_cloud;`
2. `&pt = valid_source_cloud_for_VIO->points[i];`
3. `auto pt_copy = pt;`
4. `pt_copy.intensity = 1.0;`
5. `scan_vec[i] = pt_copy;` and each point will be saved in the `scan_vec[i]` with label `is_scan_selected`
6. filtering according to the label `is_scan_selected`
if `is_scan_selected` == 0 -> the normalised x coordinate of the point is larger than 1 -> invalid points
if `is_scan_selected` == 1
`scan_W_filtered->push_back(scan_vec[i]);`
if `is_scan_selected` == 3 -> the angle of incidence is larger than the given threshold -> noise
```cpp
scan_W_filtered->push_back(scan_vec[i]);
lidar_selector->noise_cloud->push_back(scan_vec[i]);
++scan_large_angle_cnt;
```

7. `const auto &pt = featsFromMap->points[i];`
8. `V3D pt_beam{pt.x - pos_I.x(), pt.y - pos_I.y(), pt.z - pos_I.z()};`
9. `auto pt_copy = pt;`
10. `pt_copy.intensity = 1.0;`
11. the point cannot satisfy the filter condition `pt_copy.intensity = weight;` `is_map_selected` will be 3
12. `map_vec[i] = pt_copy;`
13. `map_vec` -> `map_W_filtered`

14. `display_keypatch()`
15. 


# key variables
`SubSparseMap* sub_sparse_map; // 当前帧patch地图`