

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
```cpp
struct SubSparseMap {

vector<float> align_errors;

vector<float> propa_errors; // 先验误差

vector<float> errors; // 先验误差

vector<int> index;

vector<vector<float>> patch;

vector<int> search_levels;

vector<PointPtr> voxel_points;

int valid_cnt{0};

vector<V2D> pixels;

  

SubSparseMap() {

this->propa_errors.reserve(500);

this->search_levels.reserve(500);

this->errors.reserve(500);

this->index.reserve(500);

this->patch.reserve(500);

this->voxel_points.reserve(500);

};

  

void reset() {

this->propa_errors.clear();

this->search_levels.clear();

this->errors.clear();

this->index.clear();

this->patch.clear();

this->voxel_points.clear();

}

};


class Point : boost::noncopyable

{

public:

EIGEN_MAKE_ALIGNED_OPERATOR_NEW

// enum PointType {

// TYPE_DELETED,

// TYPE_CANDIDATE,

// TYPE_UNKNOWN,

// TYPE_GOOD

// };

  

static int point_counter_; //!< Counts the number of created points. Used to set the unique id.

int id_; //!< Unique ID of the point.

Vector3d pos_; //!< 3d pos of the point in the world coordinate frame.

float x, y, z, intensity;

Vector3d normal_; //!< Surface normal at point.

Matrix3d normal_information_; //!< Inverse covariance matrix of normal estimation.

bool normal_set_; //!< Flag whether the surface normal was estimated or not.

list<FeaturePtr> obs_; //!< References to keyframes which observe the point.

size_t n_obs_; //!< Number of observations: Keyframes AND successful reprojections in intermediate frames.

int last_published_ts_; //!< Timestamp of last publishing.

int last_projected_kf_id_; //!< Flag for the reprojection: don't reproject a pt twice.

// PointType type_; //!< Quality of the point.

int n_failed_reproj_; //!< Number of failed reprojections. Used to assess the quality of the point.

int n_succeeded_reproj_; //!< Number of succeeded reprojections. Used to assess the quality of the point.

int last_structure_optim_; //!< Timestamp of last point optimization

bool have_scaled;

float value;

float weight_;

float weight_2_{1.}; // 深度调权

float weight_3_{1.}; // source畸变权重

float weight_4_{1.}; // target畸变权重

int is_valid_{1};

Vector2d pixel_;

  

float curvature_{-1.};

  

static void resetStatics();

Point(const Vector3d& pos);

Point(const Vector3d& pos, FeaturePtr ftr);

~Point();

  

void getFurthestViewObs(const Vector3d& framepos, FeaturePtr& ftr) const;

void deleteFeatureRef(FeaturePtr ftr);

  

/// Add a reference to a frame.

void addFrameRef(FeaturePtr ftr);

  

/// Remove reference to a frame.

bool deleteFrameRef(Frame* frame);

  

/// Initialize point normal. The inital estimate will point towards the frame.

void initNormal();

  

/// Check whether mappoint has reference to a frame.

FeaturePtr findFrameRef(Frame* frame);

  

bool getClosePose(const FramePtr& new_frame, FeaturePtr& ftr) const;

  

/// Get Frame with similar viewpoint.

bool getCloseViewObs(const Vector3d& pos, FeaturePtr& obs, const Vector2d& cur_px) const;

bool getBestViewObs(const Vector3d& pos, FeaturePtr& obs, const Vector2d& cur_px) const;

  

bool getCloseViewObs_test(const Vector3d& pos, FeaturePtr& obs, const Vector2d& cur_px, double& min_cos_angle) const;

  

/// Get number of observations.

inline size_t nRefs() const { return obs_.size(); }

  

/// Optimize point position through minimizing the reprojection error.

void optimize(const size_t n_iter);

  

/// Jacobian of point projection on unit plane (focal length = 1) in frame (f).

inline static void jacobian_xyz2uv(

const Vector3d& p_in_f,

const Matrix3d& R_f_w,

Matrix23d& point_jac)

{

const double z_inv = 1.0/p_in_f[2];

const double z_inv_sq = z_inv*z_inv;

point_jac(0, 0) = z_inv;

point_jac(0, 1) = 0.0;

point_jac(0, 2) = -p_in_f[0] * z_inv_sq;

point_jac(1, 0) = 0.0;

point_jac(1, 1) = z_inv;

point_jac(1, 2) = -p_in_f[1] * z_inv_sq;

point_jac = - point_jac * R_f_w;

}

};
```

