amcl takes in a laser-based map, laser scans, and transform messages, and outputs pose estimates. On startup, amcl initializes its particle filter according to the parameters provided. Note that, because of the defaults, if no parameters are set, the initial filter state will be a moderately sized particle cloud centered about (0,0,0).

#### Subscribed Topics

scan ([sensor_msgs/LaserScan](http://docs.ros.org/en/api/sensor_msgs/html/msg/LaserScan.html))

- Laser scans.

tf ([tf/tfMessage](http://docs.ros.org/en/api/tf/html/msg/tfMessage.html))

- Transforms.

initialpose ([geometry_msgs/PoseWithCovarianceStamped](http://docs.ros.org/en/api/geometry_msgs/html/msg/PoseWithCovarianceStamped.html))

- Mean and covariance with which to (re-)initialize the particle filter.

map ([nav_msgs/OccupancyGrid](http://docs.ros.org/en/api/nav_msgs/html/msg/OccupancyGrid.html))

- When the use_map_topic parameter is set, AMCL subscribes to this topic to retrieve the map used for laser-based localization. **New in navigation 1.4.2.**

#### Published Topics

amcl_pose ([geometry_msgs/PoseWithCovarianceStamped](http://docs.ros.org/en/api/geometry_msgs/html/msg/PoseWithCovarianceStamped.html))

- Robot's estimated pose in the map, with covariance.

particlecloud ([geometry_msgs/PoseArray](http://docs.ros.org/en/api/geometry_msgs/html/msg/PoseArray.html))

- The set of pose estimates being maintained by the filter.

tf ([tf/tfMessage](http://docs.ros.org/en/api/tf/html/msg/tfMessage.html))

- Publishes the transform from odom (which can be remapped via the ~odom_frame_id parameter) to map.

#### Services

global_localization ([std_srvs/Empty](http://docs.ros.org/en/api/std_srvs/html/srv/Empty.html))

- Initiate global localization, wherein all particles are dispersed randomly through the free space in the map.

request_nomotion_update ([std_srvs/Empty](http://docs.ros.org/en/api/std_srvs/html/srv/Empty.html))

- Service to manually perform update and publish updated particles.

set_map ([nav_msgs/SetMap](http://docs.ros.org/en/api/nav_msgs/html/srv/SetMap.html))

- Service to manually set a new map and pose.

#### Services Called

static_map ([nav_msgs/GetMap](http://docs.ros.org/en/api/nav_msgs/html/srv/GetMap.html))

- amcl calls this service to retrieve the map that is used for laser-based localization; startup blocks on getting the map from this service.

#### Parameters

There are three categories of ROS [Parameters](https://wiki.ros.org/Parameters) that can be used to configure the amcl node: overall filter, laser model, and odometery model.

##### Overall filter parameters

~min_particles (int, default: 100)

- Minimum allowed number of particles.

~max_particles (int, default: 5000)

- Maximum allowed number of particles.

~kld_err (double, default: 0.01)

- Maximum error between the true distribution and the estimated distribution.

~kld_z (double, default: 0.99)

- Upper standard normal quantile for (1 - p), where p is the probability that the error on the estimated distrubition will be less than kld_err.

~update_min_d (double, default: 0.2 meters)

- Translational movement required before performing a filter update.

~update_min_a (double, default: π/6.0 radians)

- Rotational movement required before performing a filter update.

~resample_interval (int, default: 2)

- Number of filter updates required before resampling.

~transform_tolerance (double, default: 0.1 seconds)

- Time with which to post-date the transform that is published, to indicate that this transform is valid into the future.

~recovery_alpha_slow (double, default: 0.0 (disabled))

- Exponential decay rate for the slow average weight filter, used in deciding when to recover by adding random poses. A good value might be 0.001.

~recovery_alpha_fast (double, default: 0.0 (disabled))

- Exponential decay rate for the fast average weight filter, used in deciding when to recover by adding random poses. A good value might be 0.1.

~initial_pose_x (double, default: 0.0 meters)

- Initial pose mean (x), used to initialize filter with Gaussian distribution.

~initial_pose_y (double, default: 0.0 meters)

- Initial pose mean (y), used to initialize filter with Gaussian distribution.

~initial_pose_a (double, default: 0.0 radians)

- Initial pose mean (yaw), used to initialize filter with Gaussian distribution.

~initial_cov_xx (double, default: 0.5*0.5 meters)

- Initial pose covariance (x*x), used to initialize filter with Gaussian distribution.

~initial_cov_yy (double, default: 0.5*0.5 meters)

- Initial pose covariance (y*y), used to initialize filter with Gaussian distribution.

~initial_cov_aa (double, default: (π/12)*(π/12) radian)

- Initial pose covariance (yaw*yaw), used to initialize filter with Gaussian distribution.

~gui_publish_rate (double, default: -1.0 Hz)

- Maximum rate (Hz) at which scans and paths are published for visualization, -1.0 to disable.

~save_pose_rate (double, default: 0.5 Hz)

- Maximum rate (Hz) at which to store the last estimated pose and covariance to the parameter server, in the variables ~initial_pose_* and ~initial_cov_*. This saved pose will be used on subsequent runs to initialize the filter. -1.0 to disable.

~use_map_topic (bool, default: false)

- When set to true, AMCL will subscribe to the map topic rather than making a service call to receive its map. **New in navigation 1.4.2**

~first_map_only (bool, default: false)

- When set to true, AMCL will only use the first map it subscribes to, rather than updating each time a new one is received. **New in navigation 1.4.2**

~selective_resampling (bool, default: false)

- When set to true, will reduce the resampling rate when not needed and help avoid particle deprivation. The resampling will only happen if the effective number of particles (_N_eff = 1/(sum(k_i^2))_) is lower than half the current number of particles. Reference: _Grisetti, Giorgio, Cyrill Stachniss, and Wolfram Burgard. "Improved techniques for grid mapping with rao-blackwellized particle filters." IEEE transactions on Robotics 23.1 (2007): 34._

##### Laser model parameters

Note that whichever mixture weights are in use should sum to 1. The beam model uses all 4: z_hit, z_short, z_max, and z_rand. The likelihood_field model uses only 2: z_hit and z_rand.

~laser_min_range (double, default: -1.0)

- Minimum scan range to be considered; -1.0 will cause the laser's reported minimum range to be used.

~laser_max_range (double, default: -1.0)

- Maximum scan range to be considered; -1.0 will cause the laser's reported maximum range to be used.

~laser_max_beams (int, default: 30)

- How many evenly-spaced beams in each scan to be used when updating the filter.

~laser_z_hit (double, default: 0.95)

- Mixture weight for the z_hit part of the model.

~laser_z_short (double, default: 0.1)

- Mixture weight for the z_short part of the model.

~laser_z_max (double, default: 0.05)

- Mixture weight for the z_max part of the model.

~laser_z_rand (double, default: 0.05)

- Mixture weight for the z_rand part of the model.

~laser_sigma_hit (double, default: 0.2 meters)

- Standard deviation for Gaussian model used in z_hit part of the model.

~laser_lambda_short (double, default: 0.1)

- Exponential decay parameter for z_short part of model.

~laser_likelihood_max_dist (double, default: 2.0 meters)

- Maximum distance to do obstacle inflation on map, for use in likelihood_field model.

~laser_model_type (string, default: "likelihood_field")

- Which model to use, either beam, likelihood_field, or likelihood_field_prob (same as likelihood_field but incorporates the beamskip feature, if enabled).

##### Odometry model parameters

If ~odom_model_type is "diff" then we use the sample_motion_model_odometry algorithm from Probabilistic Robotics, p136; this model uses the noise parameters odom_alpha1 through odom_alpha4, as defined in the book.

If ~odom_model_type is "omni" then we use a custom model for an omni-directional base, which uses odom_alpha1 through odom_alpha5. The meaning of the first four parameters is similar to that for the "diff" model. The fifth parameter capture the tendency of the robot to translate (without rotating) perpendicular to the observed direction of travel.

A [bug](https://github.com/ros-planning/navigation/issues/20) was found and fixed. But fixing the old models would have changed or broken the localisation of already tuned robot systems, so the new fixed odometry models were added as new types "diff-corrected" and "omni-corrected". The default settings of the odom_alpha parameters only fit the old models, for the new model these values probably need to be a lot smaller, see [http://answers.ros.org/question/227811/tuning-amcls-diff-corrected-and-omni-corrected-odom-models/](http://answers.ros.org/question/227811/tuning-amcls-diff-corrected-and-omni-corrected-odom-models/).

Also, another [bug](https://github.com/ros-planning/navigation/issues/499) was found but only fixed after Navigation 1.16, while the current release for Kinetic is Navigation 1.14.1. This bug only affects robot with type "omni" and "omni-corrected", where odom_alpha1 and odom_alpha4 are actually reversed. I.e. odom_alpha1 is for the translation odometry noise from robot translation-al motion, and odom_alpha4 represents the odometry rotation noise from robot's rotation motion.

~odom_model_type (string, default: "diff")

- Which model to use, either "diff", "omni", "diff-corrected" or "omni-corrected".

~odom_alpha1 (double, default: 0.2)

- Specifies the expected noise in odometry's rotation estimate from the rotational component of the robot's motion.

~odom_alpha2 (double, default: 0.2)

- Specifies the expected noise in odometry's rotation estimate from translational component of the robot's motion.

~odom_alpha3 (double, default: 0.2)

- Specifies the expected noise in odometry's translation estimate from the translational component of the robot's motion.

~odom_alpha4 (double, default: 0.2)

- Specifies the expected noise in odometry's translation estimate from the rotational component of the robot's motion.

~odom_alpha5 (double, default: 0.2)

- Translation-related noise parameter (only used if model is "omni").

~odom_frame_id (string, default: "odom")

- Which frame to use for odometry.

~base_frame_id (string, default: "base_link")

- Which frame to use for the robot base

~global_frame_id (string, default: "map")

- The name of the coordinate frame published by the localization system

~tf_broadcast (bool, default: true)

- Set this to false to prevent amcl from publishing the transform between the global frame and the odometry frame.

# How to use
1. create amcl.launch
```launch
<launch>
<node pkg="amcl" type="amcl" name="amcl" output="screen">
  <!-- Publish scans from best pose at a max of 10 Hz -->
  <param name="odom_model_type" value="diff"/><!-- 里程计模式为差分 -->
  <param name="odom_alpha5" value="0.1"/>
  <param name="transform_tolerance" value="0.2" />
  <param name="gui_publish_rate" value="10.0"/>
  <param name="laser_max_beams" value="30"/>
  <param name="min_particles" value="500"/>
  <param name="max_particles" value="5000"/>
  <param name="kld_err" value="0.05"/>
  <param name="kld_z" value="0.99"/>
  <param name="odom_alpha1" value="0.2"/>
  <param name="odom_alpha2" value="0.2"/>
  <!-- translation std dev, m -->
  <param name="odom_alpha3" value="0.8"/>
  <param name="odom_alpha4" value="0.2"/>
  <param name="laser_z_hit" value="0.5"/>
  <param name="laser_z_short" value="0.05"/>
  <param name="laser_z_max" value="0.05"/>
  <param name="laser_z_rand" value="0.5"/>
  <param name="laser_sigma_hit" value="0.2"/>
  <param name="laser_lambda_short" value="0.1"/>
  <param name="laser_lambda_short" value="0.1"/>
  <param name="laser_model_type" value="likelihood_field"/>
  <!-- <param name="laser_model_type" value="beam"/> -->
  <param name="laser_likelihood_max_dist" value="2.0"/>
  <param name="update_min_d" value="0.2"/>
  <param name="update_min_a" value="0.5"/>

  <param name="odom_frame_id" value="odom"/><!-- 里程计坐标系 -->
  <param name="base_frame_id" value="base_footprint"/><!-- 添加机器人基坐标系 -->
  <param name="global_frame_id" value="map"/><!-- 添加地图坐标系 -->

  <param name="resample_interval" value="1"/>
  <param name="transform_tolerance" value="0.1"/>
  <param name="recovery_alpha_slow" value="0.0"/>
  <param name="recovery_alpha_fast" value="0.0"/>
</node>
</launch>

```
2. launch the amcl.launch and map_server
```bash
<launch>
    <!-- 设置地图的配置文件 -->
    <arg name="map" default="nav.yaml" />
    <!-- 运行地图服务器，并且加载设置的地图-->
    <node name="map_server" pkg="map_server" type="map_server" args="$(find mycar_nav)/map/$(arg map)"/>
    <!-- 启动AMCL节点 -->
    <include file="$(find mycar_nav)/launch/amcl.launch" />
    <!-- 运行rviz -->
    <node pkg="rviz" type="rviz" name="rviz"/>
</launch>
```
