- [x] completed the lidar degeneration function
- [x] body building
- [ ] boundary points filter
	current problems
	- [x] where should the boundary remove function be put in the fastlivo2
	```cpp
	if (feats_undistort->empty() || (feats_undistort == nullptr)) 
	{
	  std::cout << "[ LIO ]: No point!!!" << std::endl;
	  return;
	}
	// **就在这两行之间插入**
	double t0 = omp_get_wtime();
	
	```
	why?
	`feats_undistort` 已经由 IMU 去畸变处理好； 检查空点云并退出后，确保有效点云存在；你要基于 `feats_undistort` 的坐标系和 `state_propagat` 执行拖点检测；而且拖点处理的逻辑需要尽早执行，**在下采样（`downSizeFilterSurf.filter`）之前**。


	- [x] what is the alternative of the LidarMeasures.lidar_end_time in fastlivo2
	- [ ] 
	```cpp
	T_W_L_pose = Pose(state_propagat.rot_end, state_propagat.pos_end,LidarMeasures.lidar_frame_end_time);
	```
	why?
	```cpp
	meas.lidar_frame_end_time = meas.lidar_frame_beg_time + meas.lidar->points.back().curvature / double(1000);
		
	if (imu_en && last_timestamp_imu < meas.lidar_frame_end_time)
	
	{ // waiting imu message needs to be
	
	// larger than _lidar_frame_end_time,
	
	// make sure complete propagate.
	
	// ROS_ERROR("out sync");
	
	return false;
	
	}
```
	
	





modification log
1.  added some libraries: common, LOAM
2.  in the types.h, added some variable types for the boundary remove function
3. cite the common/common.h in the common_lib.h
4. cite the utils/types.h in LOAM/utility.h
5. cite the utility/cloud_process.h in common.h
6. cite the utils/types.h in cloud_process.h
7. cite the utils/types.h in preprocess.h







common_lib.h
```cpp
#include <utils/so3_math.h>
#include <utils/types.h>
#include <utils/color.h>
#include <opencv2/opencv.hpp>
#include <sensor_msgs/Imu.h>
#include <sophus/se3.h>
#include <tf/transform_broadcaster.h>
// for the boundary remove and far points filter, added by zewen
#include <common/common.h>
```

feature.h
```cpp
#include "visual_point.h"
```

frame.h
```cpp
#include <boost/noncopyable.hpp>
#include <vikit/abstract_camera.h>
```

IMU_Processing.h
```cpp
#include <Eigen/Eigen>
#include "common_lib.h"
#include <condition_variable>
#include <nav_msgs/Odometry.h>
#include <utils/so3_math.h>
```

LIVMapper.h
```cpp
#include "IMU_Processing.h"
#include "vio.h"
#include "preprocess.h"
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <nav_msgs/Path.h>
#include <vikit/camera_loader.h>
// for the boundary remove and far points filter, added by zewen
#include <common_lib.h>
#include <LOAM/lidar_odometry.h>
```

preprocess.h
```cpp
#include "common_lib.h"
#include <livox_ros_driver/CustomMsg.h>
#include <pcl_conversions/pcl_conversions.h>
```

vio.h
```cpp
#include "voxel_map.h"
#include "feature.h"
#include <opencv2/imgproc/imgproc_c.h>
#include <pcl/filters/voxel_grid.h>
#include <set>
#include <vikit/math_utils.h>
#include <vikit/robust_cost.h>
#include <vikit/vision.h>
#include <vikit/pinhole_camera.h>
```

visual_point.h
```cpp
#include <boost/noncopyable.hpp>
#include "common_lib.h"
#include "frame.h"
```

voxel_map.h
```cpp
#include "common_lib.h"
#include <Eigen/Dense>
#include <fstream>
#include <math.h>
#include <mutex>
#include <omp.h>
#include <pcl/common/io.h>
#include <ros/ros.h>
#include <thread>
#include <unistd.h>
#include <unordered_map>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
```

types.h
```cpp
#include <Eigen/Eigen>
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <preprocess.h> // added by zewen for the boundary remove and far points filter based on ac1 fastlivo
```

utility.h
```cpp
// added by zewen for the fast-livo2 boundary remove and far points filter
#include "utils/types.h"
```

lidar_odometry.h
```cpp
#include "image_projection.h"
#include "feature_association.h"
#include "common/utility/yaml_reader.hpp"
```

feature_association.h
```cpp
#include "utility.h"
```

image_projection.h
```cpp
#include "LOAM/utility.h"
#include "common_lib.h"
```


common/utility.h
```cpp
#include "utility/yaml_reader.hpp"
#include "utility/math.h"
#include "msg/imu_msg.h"
#include "msg/pose_msg.h"
// #include "msg/lidar_msg.h"
// #include "msg/cloud_msg.h"
#include "utility/cloud_process.h"
```

cloud_process.h
```cpp
#include <utils/types.h> // added by zewen for the boundary remove and far points filter
#include "common/common.h"
```


pose_msg.h
```cpp
#include "common/common.h"
```


MD:
types.h
common.h