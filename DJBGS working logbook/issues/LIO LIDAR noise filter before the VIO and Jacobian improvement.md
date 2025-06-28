current issue
![[adefaa453af4299b0f16e8835fb37f90.jpg]]

在RS-FASTLIVO这一功能的实现部分，所有降采样的点云的法线方向光心射线方向的夹角会被计算，然后夹角超过阈值的点的权重会通过 `pt_copy.intensity = weight;` 来赋予。

那么，需要保留的点和噪点会有不同的权重

然后，请问，这里使用过权重之间的区别对点进行过滤吗？

如果是这样的话，这一部分的代码在哪？是这个ProjCloudToImageToGetFeature 里吗？

因为这个ProjCloudToImageToGetFeature对将采样的点云做了投影以方便投影点的reference path对应的图块和现图块之间的匹配，所以这个滤除应该在这个函数的开始部分，可我没找到



没有直接过滤点。存到了点的weight_字段，在优化时用来给光度误差降权。
Jimg = Jimg * (1.0/scale) * pt->weight_ * pt->weight_2_ * pt->weight_3_ * pt->weight_4_;


# current adjustment

1. the structure of one point, the curvature and the intensity are added
```cpp
typedef struct pointWithVar

{

Eigen::Vector3d point_b; // point in the lidar body frame

Eigen::Vector3d point_i; // point in the imu body frame

Eigen::Vector3d point_w; // point in the world frame

Eigen::Matrix3d var_nostate; // the var removed the state covarience

Eigen::Matrix3d body_var;

Eigen::Matrix3d var;

Eigen::Matrix3d point_crossmat;

Eigen::Vector3d normal;

  

// add by zewen for the Jacobian computation

int intensity; // intensity of the point, used for the point cloud

int curvature; // curvature of the point, used for the point cloud

pointWithVar()

{

var_nostate = Eigen::Matrix3d::Zero();

var = Eigen::Matrix3d::Zero();

body_var = Eigen::Matrix3d::Zero();

point_crossmat = Eigen::Matrix3d::Zero();

point_b = Eigen::Vector3d::Zero();

point_i = Eigen::Vector3d::Zero();

point_w = Eigen::Vector3d::Zero();

normal = Eigen::Vector3d::Zero();

intensity = 1; // initialize intensity to 0

curvature = 0; // initialize curvature to 0

};

} pointWithVar;
```


2. this is the class for a point in the visual submap, the weights and curvature are added
```cpp
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

float weight_{1.}; // noise weight

float weight_2_{1.}; // 深度调权

float weight_3_{1.}; // source畸变权重

float weight_4_{1.}; // target畸变权重

int curvature = 0; // 曲率，0表示平坦，1表示曲率较大

  
  
  

VisualPoint(const Vector3d &pos);

~VisualPoint();

void findMinScoreFeature(const Vector3d &framepos, Feature *&ftr) const;

void deleteNonRefPatchFeatures();

void deleteFeatureRef(Feature *ftr);

void addFrameRef(Feature *ftr);

bool getCloseViewObs(const Vector3d &pos, Feature *&obs, const Vector2d &cur_px) const;

};
```


3. the structure of a visual submap, the coordinate in pixel of a visual point in the submap is added
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

  

// added by zewen for the undistortion weight adjustment

vector<Vector2d> pixels; // the coordinate of points in pixel map, used for the undistortion weight adjustment

  

SubSparseMap()

{

propa_errors.reserve(SIZE_LARGE);

errors.reserve(SIZE_LARGE);

warp_patch.reserve(SIZE_LARGE);

search_levels.reserve(SIZE_LARGE);

voxel_points.reserve(SIZE_LARGE);

inv_expo_list.reserve(SIZE_LARGE);

add_from_voxel_map.reserve(SIZE_SMALL);

pixels.reserve(SIZE_LARGE);

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

pixels.clear();

}

};
```
4. the weight computational algorithms are added