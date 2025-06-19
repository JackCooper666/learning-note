EstimateLIOState()
1. `feat_undistort` -> `PreprocessCloud(feat_undistort)` this function will filter the tailing points and far points, then downsample the filtered points to get the `feats_down_body`
2. 




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
