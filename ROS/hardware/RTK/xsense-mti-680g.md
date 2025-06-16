# software download
## MT manager install
refer to:
https://base.movella.com/s/article/MT-Manager-Installation-Guide-for-ubuntu-20-04-and-22-04?language=en_US

1. Sofware Download
	1. Please download the MT Software Suite under the MTi Products section：[https://www.movella.com/support/software-documentation](https://www.movella.com/support/software-documentation
2. extract the software
```bash
sudo tar -xf MT_Software_Suite_linux-x64_2025.0_b20241121.1_r1732180523.tar.gz
sudo chmod -R o+rw MT_Software_Suite_linux-x64_2025.0/
cd MT_Software_Suite_linux-x64_2025.0
sudo tar -xf mtmanager_linux-x64_2025.0.tar.gz
sudo chmod -R o+rw mtmanager/
```
3. install the dependencies for MT Manager for ubuntu 20.04
Refer to the readme in the doc (located at mtmanager/linux-64/doc/MTM.README) to install dependencies for MT Manager.
```bash
sudo apt update
sudo apt install qt5-default
sudo apt-get update -y
sudo apt-get install -y libqt5opengl5
sudo apt-get install -y libusb-1.0-0
sudo apt-get install -y libxcb-xinerama0
sudo apt-get install -y libxcb-xinput0
sudo apt-get install -y libdouble-conversion1
```

libdouble-conversion.so.1
```bash
wget http://ftp.br.debian.org/debian/pool/main/d/double-conversion/libdouble-conversion1_3.1.0-3_amd64.deb
sudo chmod +x libdouble-conversion1_3.1.0-3_amd64.deb
sudo dpkg -i libdouble-conversion1_3.1.0-3_amd64.deb
```

libicu18n.so.60
Make sure you have the bionic-security source is in your /etc/apt/sources.list:
```bash
sudo gedit /etc/apt/sources.list
```
Add this to the last line if it is not present:
```bash
deb http://security.ubuntu.com/ubuntu bionic-security main
```
then run:  
```bash
sudo apt-get update
sudo apt-get install libicu60
```

run mtmanager
run your mtmanager (located at: mtmanager/linux-x64/bin/)
```bash
./mtmanager
```

## workspace and package downloading
refer to 
https://github.com/xsenssupport/Xsens_MTi_ROS_Driver_and_Ntrip_Client/tree/main#

install dependency:

```
sudo apt install ros-[ROSDISTRIBUTION]-nmea-msgs
sudo apt install ros-[ROSDISTRIBUTION]-mavros-msgs
```

for example for ROS Noetic(use `rosversion -d` to get your version):

```
sudo apt install ros-noetic-nmea-msgs
sudo apt install ros-noetic-mavros-msgs
```

clone the source file to your `catkin_ws`, and run the code below:

```
cd ~/catkin_ws
catkin_make
```

Source the `/devel/setup.bash` file inside your catkin workspace

```
source ./devel/setup.bash
```

# use RTK
## device setting
- For MTi-680(G), the UTC Time, PvtData needs to be enabled, in order to get GPGGA data for topic `/nmea`, which will be used for the Ntrip Client:
    - MT Manager - Device Settings - Output Configuration , select "UTC Time, Sample TimeFine, Status Word, Latitude and Longitude" and other required data, click "Apply",
- or your could change the `enable_deviceConfig` in [xsens_mti_node.yaml](https://github.com/xsenssupport/Xsens_MTi_ROS_Driver_and_Ntrip_Client/blob/main/src/xsens_ros_mti_driver/param/xsens_mti_node.yaml) to true and change the `pub_utctime`, `pub_gnss` to true, then change the other desired output parameters as listed in the [xsens_mti_node.yaml](https://github.com/xsenssupport/Xsens_MTi_ROS_Driver_and_Ntrip_Client/blob/main/src/xsens_ros_mti_driver/param/xsens_mti_node.yaml) for the complete sensor configurations.
## How to Use:

change the credentials/servers/mountpoint in `src/ntrip/launch/ntrip.launch` to your own one.

open two terminals:

```
roslaunch xsens_mti_driver xsens_mti_node.launch
```

or with the 3D display rviz:

```
roslaunch xsens_mti_driver display.launch
```

and then

```
roslaunch ntrip ntrip.launch
```