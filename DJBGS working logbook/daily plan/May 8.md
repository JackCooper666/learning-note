- [x] valid point matching function
- [ ] body building
- [ ] check other params in the LIO system


In the FAST-LIVO-ARC-NUS 
the p2plane_thresh is used in the point-to-plane residual calculation and filter out

The following code is the code for this function

```cpp
for (int i = 0; i < feats_down_size; i++) {
PointType &point_body = feats_down_body->points[i];
PointType &point_world = feats_down_world->points[i];
point_world.normal_x = point_world.normal_y = point_world.normal_z = 99;
V3D p_body(point_body.x, point_body.y, point_body.z);
pointBodyToWorld(&point_body, &point_world);
vector<float> pointSearchSqDis(NUM_MATCH_POINTS);
auto &points_near = Nearest_Points[i];
uint8_t search_flag = 0;
double search_start = omp_get_wtime();
if (nearest_search_en) {
/** Find the closest surfaces in the map **/
ikdtree.Nearest_Search(point_world, NUM_MATCH_POINTS, points_near,
pointSearchSqDis);
point_selected_surf[i] =
pointSearchSqDis[NUM_MATCH_POINTS - 1] > 5 ? 0 : 1;
kdtree_search_time += omp_get_wtime() - search_start;
kdtree_search_counter++;
}
if (!point_selected_surf[i] || points_near.size() < NUM_MATCH_POINTS)
continue;
  
VF(4) pabcd; // the normal vector of the surface, commended by zewen
point_selected_surf[i] = 0;
if (esti_plane(pabcd, points_near, 0.1f)) //(planeValid)

// commended by zewen
// the esti_plane() used to calculate the normal vector of the surface

{
float pd2 = pabcd(0) * point_world.x + pabcd(1) * point_world.y +
pabcd(2) * point_world.z + pabcd(3);
// commended by zewen
// the distance between the taget point and the selected surface

float s = 1 - 0.9 * fabs(pd2) / sqrt(p_body.norm());
// commended by zewen, this is the normalization

if (s > 0.9) {
point_selected_surf[i] = 1;
normvec->points[i].x = pabcd(0);
normvec->points[i].y = pabcd(1);
normvec->points[i].z = pabcd(2);
normvec->points[i].intensity = pd2;
res_last[i] = abs(pd2); 
// commended by zewen, this is the point-to-plane residual
}
point_world.normal_x = pabcd(0);
point_world.normal_y = pabcd(1);
point_world.normal_z = pabcd(2);
point_body.normal_x = pabcd(0);
point_body.normal_y = pabcd(1);
point_body.normal_z = pabcd(2);
}
}
```


```cpp
// LINFO<<"pca time test: "<<pca_time1<<" "<<pca_time2<<END;
effct_feat_num = 0;
laserCloudOri->resize(feats_down_size);
corr_normvect->resize(feats_down_size);
valid_source_indices->indices.reserve(feats_down_size);
invalid_source_indices->indices.reserve(feats_down_size);
invalid_reason.resize(feats_down_size);
  
for (int i = 0; i < feats_down_size; i++) {
if (point_selected_surf[i] && (res_last[i] <= p2plane_thresh)) {
laserCloudOri->points[effct_feat_num] = feats_down_body->points[i];
// commended by zewen, this line stores the points passed the residual checking. These points will be used in ESIKF optimization for the Measurement Jaccobin Matrix "H" calculation

// feats_down_body->points[i].curvature = abs(res_last[i]);
// feats_down_world->points[i].curvature = abs(res_last[i]);
corr_normvect->points[effct_feat_num] = normvec->points[i];
valid_source_indices->indices.push_back(i);
total_residual += res_last[i];
// commended by zewen, this is to get the total residual for ESIKF optimization
effct_feat_num++;
// commended by zewen, this is to get the total residual for the ESIKF optimization

} else {
invalid_source_indices->indices.push_back(i);
if (!point_selected_surf[i])
invalid_reason[i] = 10;
else if (res_last[i] > 0.5)
invalid_reason[i] = 20;
}
}
```


for the FAST-LIVO2, it has the similar point-to-plane residual calculation and filter out

1. create memory space for the down-sampled point cloud
```cpp
vector<pointWithVar>().swap(pv_list_);
pv_list_.resize(feats_down_size_);
```
2. put the down-sampled point cloud into the memory space
```cpp
for (size_t i = 0; i < feats_down_body_->size(); i++)

{
	pointWithVar &pv = pv_list_[i];
	pv.point_b << feats_down_body_->points[i].x, feats_down_body_->points[i].y, feats_down_body_->points[i].z;
	pv.point_w << world_lidar->points[i].x, world_lidar->points[i].y, world_lidar->points[i].z;
	M3D cov = body_cov_list_[i];
	M3D point_crossmat = cross_mat_list_[i];
	cov = state_.rot_end * cov * state_.rot_end.transpose() + (-point_crossmat) * rot_var * (-point_crossmat.transpose()) + t_var;
	pv.var = cov;
	pv.body_var = body_cov_list_[i];
}

ptpl_list_.clear();
```

3. calculate the point-to-plane residual and filter out the isolate points
```cpp
BuildResidualListOMP(pv_lits_,ptpl_list_)
// pv_list_ is the input
// ptpl_list_ is the filter result

void VoxelMapManager::BuildResidualListOMP(std::vector<pointWithVar> &pv_list, std::vector<PointToPlane> &ptpl_list)

{

// declarasion
int max_layer = config_setting_.max_layer_;

double voxel_size = config_setting_.max_voxel_size_;

double sigma_num = config_setting_.sigma_num_;

std::mutex mylock;

ptpl_list.clear();

std::vector<PointToPlane> all_ptpl_list(pv_list.size());

std::vector<bool> useful_ptpl(pv_list.size());

std::vector<size_t> index(pv_list.size());

for (size_t i = 0; i < index.size(); ++i)

{

index[i] = i;

useful_ptpl[i] = false;

}

#ifdef MP_EN

omp_set_num_threads(MP_PROC_NUM);

#pragma omp parallel for

#endif

for (int i = 0; i < index.size(); i++)

{

pointWithVar &pv = pv_list[i];

float loc_xyz[3];

for (int j = 0; j < 3; j++)

{

loc_xyz[j] = pv.point_w[j] / voxel_size;

if (loc_xyz[j] < 0) { loc_xyz[j] -= 1.0; }

}

VOXEL_LOCATION position((int64_t)loc_xyz[0], (int64_t)loc_xyz[1], (int64_t)loc_xyz[2]);

auto iter = voxel_map_.find(position);

if (iter != voxel_map_.end())

{

VoxelOctoTree *current_octo = iter->second;

PointToPlane single_ptpl;

bool is_sucess = false;

double prob = 0;

build_single_residual(pv, current_octo, 0, is_sucess, prob, single_ptpl);

if (!is_sucess)

{

VOXEL_LOCATION near_position = position;

if (loc_xyz[0] > (current_octo->voxel_center_[0] + current_octo->quater_length_)) { near_position.x = near_position.x + 1; }

else if (loc_xyz[0] < (current_octo->voxel_center_[0] - current_octo->quater_length_)) { near_position.x = near_position.x - 1; }

if (loc_xyz[1] > (current_octo->voxel_center_[1] + current_octo->quater_length_)) { near_position.y = near_position.y + 1; }

else if (loc_xyz[1] < (current_octo->voxel_center_[1] - current_octo->quater_length_)) { near_position.y = near_position.y - 1; }

if (loc_xyz[2] > (current_octo->voxel_center_[2] + current_octo->quater_length_)) { near_position.z = near_position.z + 1; }

else if (loc_xyz[2] < (current_octo->voxel_center_[2] - current_octo->quater_length_)) { near_position.z = near_position.z - 1; }

auto iter_near = voxel_map_.find(near_position);

if (iter_near != voxel_map_.end()) { build_single_residual(pv, iter_near->second, 0, is_sucess, prob, single_ptpl); }

}

if (is_sucess)

{

mylock.lock();

useful_ptpl[i] = true;

all_ptpl_list[i] = single_ptpl;

mylock.unlock();

}

else

{

mylock.lock();

useful_ptpl[i] = false;

mylock.unlock();

}

}

}

for (size_t i = 0; i < useful_ptpl.size(); i++)

{

if (useful_ptpl[i]) { ptpl_list.push_back(all_ptpl_list[i]); }

}

}

void VoxelMapManager::build_single_residual(pointWithVar &pv, const VoxelOctoTree *current_octo, const int current_layer, bool &is_sucess,

double &prob, PointToPlane &single_ptpl)

{

int max_layer = config_setting_.max_layer_;

double sigma_num = config_setting_.sigma_num_;

  

double radius_k = 3;

Eigen::Vector3d p_w = pv.point_w;

if (current_octo->plane_ptr_->is_plane_)

{

VoxelPlane &plane = *current_octo->plane_ptr_;

Eigen::Vector3d p_world_to_center = p_w - plane.center_;

float dis_to_plane = fabs(plane.normal_(0) * p_w(0) + plane.normal_(1) * p_w(1) + plane.normal_(2) * p_w(2) + plane.d_);

float dis_to_center = (plane.center_(0) - p_w(0)) * (plane.center_(0) - p_w(0)) + (plane.center_(1) - p_w(1)) * (plane.center_(1) - p_w(1)) +

(plane.center_(2) - p_w(2)) * (plane.center_(2) - p_w(2));

float range_dis = sqrt(dis_to_center - dis_to_plane * dis_to_plane);

  

if (range_dis <= radius_k * plane.radius_)

{

Eigen::Matrix<double, 1, 6> J_nq;

J_nq.block<1, 3>(0, 0) = p_w - plane.center_;

J_nq.block<1, 3>(0, 3) = -plane.normal_;

double sigma_l = J_nq * plane.plane_var_ * J_nq.transpose();

sigma_l += plane.normal_.transpose() * pv.var * plane.normal_;

if (dis_to_plane < sigma_num * sqrt(sigma_l))

{

is_sucess = true;

double this_prob = 1.0 / (sqrt(sigma_l)) * exp(-0.5 * dis_to_plane * dis_to_plane / sigma_l);

if (this_prob > prob)

{

prob = this_prob;

pv.normal = plane.normal_;

single_ptpl.body_cov_ = pv.body_var;

single_ptpl.point_b_ = pv.point_b;

single_ptpl.point_w_ = pv.point_w;

single_ptpl.plane_var_ = plane.plane_var_;

single_ptpl.normal_ = plane.normal_;

single_ptpl.center_ = plane.center_;

single_ptpl.d_ = plane.d_;

single_ptpl.layer_ = current_layer;

single_ptpl.dis_to_plane_ = plane.normal_(0) * p_w(0) + plane.normal_(1) * p_w(1) + plane.normal_(2) * p_w(2) + plane.d_;

}

return;

}

else

{

// is_sucess = false;

return;

}

}

else

{

// is_sucess = false;

return;

}

}

else

{

if (current_layer < max_layer)

{

for (size_t leafnum = 0; leafnum < 8; leafnum++)

{

if (current_octo->leaves_[leafnum] != nullptr)

{

  

VoxelOctoTree *leaf_octo = current_octo->leaves_[leafnum];

build_single_residual(pv, leaf_octo, current_layer + 1, is_sucess, prob, single_ptpl);

}

}

return;

}

else { return; }

}

}
```

