refer to this link
https://robosense-wiki-en.readthedocs.io/en/latest/

# AC Viewer
AC Viewer is a software designed specifically for Active Camera, which can be used to display real-time data (including point clouds, images, etc.) from all Active Cameras connected to the computer.  
Through AC Viewer, users can easily view, record, and store sensor data for later use.
**Hardware preparation:**
- Active Camera x 1
- power cable
- data cable
- PC x 1
**PC configuration:**

|              |                                     |                                           |
| ------------ | ----------------------------------- | ----------------------------------------- |
|              | Minimum Requirements                | Recommended configuration                 |
| CPU          | 7th Gen Intel Core i3 or equivalent | Intel 11500 or above  <br>Mac M2 or above |
| GPU          | Integrated graphics                 | NVIDIA RTX 3060 or higher                 |
| RAM          | 8GB                                 | 16GB or more                              |
| Connectivity | USB3.0                              | USB3.0                                    |

**Supported Operating Systems:**
- windows 10 x64
- Ubuntu 20.04 x64

**Physical connection:**

**Software download:**
Ubuntu 20.04
https://cdn.robosense.cn/ACViewer%20Release/AcViewer_Linux_x86_64_release_1.0.11.deb

**Note**
Sometime the Viewer cannot find the ac1 and will publish an error "need calibration file"
suggest to use the driver directly.
# Driver
## C Driver[](https://robosense-wiki-en.readthedocs.io/en/latest/ac_studio/driver.html#id1 "Link to this heading")

This is the driver for RoboSense robotic sensor products. It is developed based on C/C++ language, providing users with underlying driver functions, responsible for configuring, initializing, calibrating the device, and implementing hardware device detection and status management, ensuring efficient operation of the sensor. It also provides developer interfaces for the device, supporting sensor configuration, data collection, device control, and other functions, facilitating developers to quickly integrate and use the device.

Source Code: [AC1 Driver](https://github.com/RoboSense-LiDAR/rs_driver/tree/dev_opt_AC1)

## ROS Driver[](https://robosense-wiki-en.readthedocs.io/en/latest/ac_studio/driver.html#ros-driver "Link to this heading")

The ROS driver is a brand-new ROS package specifically designed to interface with robotic sensor products manufactured by RoboSense. This driver is capable of operating on systems such as Ubuntu 20.04 with ROS Noetic environment and ARM Debian 12, among others.

Source Code: [AC1 ROS Driver](https://github.com/RoboSense-Robotics/robosense_ac_ros_sdk_infra)

it has the rviz, but you need to acticate it in the start.launch

## ROS2 Driver[](https://robosense-wiki-en.readthedocs.io/en/latest/ac_studio/driver.html#ros2-driver "Link to this heading")

ROS2 driver is a brand new ROS2 package, specifically designed to connect RoboSense robotic sensor products. This driver can run on operating systems with ROS2 environment (humble, jazzy) installed, such as ubuntu18.04/20.04/22.04, Windows, Mac, ARM Debian12, etc.

Source Code: [AC1 ROS2 Driver](https://github.com/RoboSense-Robotics/robosense_ac_ros2_sdk_infra)

### errors during the colcon build
/usr/bin/ld: cannot find -lAVDEVICE_LIBRARY-NOTFOUND: No such file or directory
this may be caused by the FFmpeg, your may need to install the relevant libs
```bash
sudo apt update
sudo apt install libavdevice-dev libavfilter-dev libpostproc-dev libavformat-dev libavcodec-dev libswscale-dev
```
---
--- stderr: ac_codec
CMake Error: The following variables are used in this project, but they are set to NOTFOUND.
Please set them or make sure they are set and tested correctly in the CMake files:
AVDEVICE_LIBRARY
linked by target "codec_node" in directory /robosense_ac_ros2_sdk_infra/modules/ac_codec
AVFILTER_LIBRARY
linked by target "codec_node" in directory /robosense_ac_ros2_sdk_infra/modules/ac_codec
POSTPROC_LIBRARY
this means the critical dependencies missing, please refer to [modules/ac_driver/README.md](https://github.com/RoboSense-Robotics/robosense_ac_ros2_sdk_infra/blob/main/modules/ac_driver/README.md).
for X86 board
```bash
sudo apt-get update
sudo apt-get install libavformat-dev libavdevice-dev libavcodec-dev
```
---
For Ubuntu 22.04 you may get this error:
The following signatures were invalid: EXPKEYSIG F42ED6FBAB17C654 Open Robotics <info@osrfoundation.org> Hit:9 http://security.ubuntu.com/ubuntu jammy-security InRelease

this happens becuase
1. **ROS (Robot Operating System)** signs its repository packages with a **GPG key** to ensure authenticity.
2. **This key expired** (common in Linux repositories for security reasons).
3. Your system can no longer verify ROS packages because the old key is invalid.

please try this command:
```bash
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
```


# Calibration
## camera intrinsic

## camera to 


