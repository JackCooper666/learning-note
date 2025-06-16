# software download
## MT manager install
refer to:
https://base.movella.com/s/article/MT-Manager-Installation-Guide-for-ubuntu-20-04-and-22-04?language=en_US

https://wiki.ros.org/xsens_mti_driver

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

## access authority setting
in your BIOS please shutdown your security protection, when using linux, as the protection will eject any installization for the custom core.

plugin the xsens-mti-680g to your pc, check whether the `ttyUSB0` is in your /dev by:
```bash
ls /dev
```
For the MTi-1/600/Sirius product series, such as 680g, where the FTDI chip was used, try the following steps:

```bash
sudo /sbin/modprobe ftdi_sio
echo 2639 0300 | sudo tee /sys/bus/usb-serial/drivers/ftdi_sio/new_id
```

Make sure you are in the correct group (often dialout or uucp) in order to access the device. You can test this with:

```bash
ls -l /dev/ttyUSB0

crw-rw---- 1 root dialout 188, 0 May  6 16:21 /dev/ttyUSB0
```

your terminal should be in the correct group, the group for the xsens-mti-680g is dialout
you can check the group by 

```bash
groups
```

if there is not a dialout, you can fix this in two ways:
1) Add yourself to the correct group. You can add yourself to it by using your distributions user management tool, or call:
```bash
sudo usermod -G dialout -a $USER
```

	Be sure to replace dialout with the actual group name if it is different. After adding yourself to the group, either relogin to your user, or add the current terminal session to the group:

```bash
newgrp dialout
```

2) Use udev rules. Alternatively, put the following rule into /etc/udev/rules.d/99-custom.rules:

```bash
sudo gedit /etc/udev/rules.d/99-custom.rules
# the 99-custom.rules needs to be created by yourself
```
	adding the following line in the `99-custom.rules`

```
SUBSYSTEM=="tty", ATTRS{idVendor}=="2639", ACTION=="add", GROUP="$GROUP", MODE="0660"
```
	Change $GROUP into your desired group (e.g. adm, plugdev, or usb).

then reboot your pc
```bash
sudo reboot
```
You can specify your own port and baud rate in the [`xsens_mti_node.yaml`](https://github.com/xsenssupport/Xsens_MTi_ROS_Driver_and_Ntrip_Client/blob/main/src/xsens_ros_mti_driver/param/xsens_mti_node.yaml) file:

```yaml
// change the scan_for_devices to `false` and uncomment/change the port name and baud rate to your own values (by default it is 115200, unless you have changed the value with MT Manager).
scan_for_devices: false # set to false w=otherwise the port will not work
port: '/dev/ttyUSB0'
# baudrate: 115200
```
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