# 1. Overview
This is an instruction to demenstrate how to integrate ublox f9p within windows and ros2 step by stepf
%% # 1. Equipment overview
this is the overview of the equipment. %%
# 2. Windows
The RTK localization includes two parts: the GPS localization, and the NTRIP localization correction. This section will present a detailed instruction for achieving the RTK localization on Windows. 
## 2.1 Download U-center
1. Please, use the following link to download the u-center
	https://www.u-blox.com/en/product/u-center
2. In the Web page, please choose the u-center (highlighted by red box) not the u-center 2, as Figure 1.
![[u-center.png]]
\[Figure 1\]: U-center download
## 2.2 Connect the GPS
**Steps:**
1. Click the Receiver -> Connection to choose the serial port of the ublox as Figure below.
![[win_port_selection.png]]

2. Then, set the baudrate of the serial communication.



3.  Make sure the connection icon is flashing in the bottom status bar. This indicates that the serial communication between the computer and the GNSS device is working.
![[com_connect.png]]


## 2.3 Verification the GPS connection and situation
The GPS testing need to be executed at empty outdoor environment. When the Fix mode on the right side of the interface shows 3D (green), it means that the right side is working normally, as Figure shows


## 2.4 Connect the NTRIP Client
**Steps:**
1. Make Sure your PC connects with internet. The personal Hotspot is recommended Because, the NTRIP access will be rejected by the Firewall sometime.  
2. Click the Receiver-> NTRIP Client, then key your host, port, username and password like the following Figure 2 shows
3. Click the "Update source table," which will search the valid mount points, then choose your mount point like the following Figure 2 shows. According to our previous test, the RTK_SiReNT_32 can provide an accurate localization result.




4. If the connection is successful, the ntrip connection icon will be green in the bottom status bar as Figure.


## 2.5 Check the RTK status
The RTK status should be tested under empty outdoor environment. The RTK status will be shown at the last word of the  Fix Mode like the followings Figures. The "Fix" in Figure means the RTK status is fix, the "Float" in Figure means the RTK status is float.


In addition, Figure is our test result of RTK status by Xsens mti 680g. Please have a look, as reference. The green points are RTK fix status, the orange points are RTK float status, and the red points are RTK invalid status.


## 2.6 Insert the google map
Meanwhile, the u-center can show the RTK localization result on the google map in real-time, like Figure.

**Prerequisites**
1. register a google map static map API through the following link
https://developers.google.com/maps/documentation/static-maps/?hl=en

**Steps:**
1. input your google map static API at Tool->Preferences->Access Tokens, then click "Apply", then "OK"
2. open the "Map View" 



# 3. ROS2
## 3.1 Pre-setting on U-center WINDOWS
The Pre-setting on u-center includes two parts: the serial communication setting and the output messages setting.
##### Serial communication setting
**Steps:**
1. config the port under **menu bar  -> View -> Message View -> UBX -> CFG -> PRT (Ports)** like following Figure

2. Output frequency configuration under **menu bar  -> View -> Message View -> UBX -> CFG -> RATE(Rates)** like following Figure


3. After the modification is completed, finally choose to save the parameters under the **menu bar  -> View -> Message View -> UBX -> CFG -> CFG(Configuration)** like following Figure

##### Output messages setting
**Steps:**
1. Configure the receiver to output raw data and navigation messages
	menu bar  -> View -> Message View ->UBX -> RXM(Receiver Manager) -> UBX-RXM-RAWX(Multi-GNSS-Raw-Measurement Data)
	menu bar  -> View -> Message View ->UBX -> RXM(Receiver Manager) -> UBX-RXM-SFRBX

	Please right click them and choose enable.

2. Configure the receiver to output navigation results in UBX format
	menu bar  -> View -> Message View ->UBX -> UBX-NAV-PVT

	Please right click them and choose enable.
	
3. Configure the receiver to output NMEA protocol related statements
	menu bar -> View -> Message View -> NMEA
	 
	 Please right click it and choose enable Child Messages, but please disable the message **PUBX** under the NMEA
	 
4. After the modification is completed, finally choose to save the parameters under the **menu bar  -> View -> Message View -> UBX -> CFG -> CFG(Configuration)** like following Figure


## 3.2 Connect Ubuntu with ublox F9P
##### 3.2.1 Update your ros2
To manage dependencies in ROS 2, update your package list and installs **ros-dev-tools**, which includes **rosdep** and other useful development tools for ROS 2.
```bash
sudo apt update && sudo apt install ros-dev-tools
```

##### 3.2.2 Find your RTK receiver on your PC
1. Connect your receiver to the PC via the USB port. 
2. The receiver should be automatically configured. To verify this, open Terminal and type the command. You should see **/dev/ttyACM0** (or a similar device, e.g., **/dev/ttyACM1**).
```bash
ls /dev/ttyACM*
```


3. To check the GPS Stream from RTK receiver, run the command in the Terminal. It shows the raw GPS data streaming from the receiver. Press **Ctrl + C** to stop.
```bash
sudo cat /dev/ttyACM0
```
 **Tip:** If you don’t see any output or the device is missing, make sure your user has the appropriate permissions (e.g., being in the dialout group). You can add yourself with the command below. Afterward, log out and log back in for the changes to take effect.
 ```bash
 sudo usermod -a -G dialout $USER
 sudo reboot
 ```


## 3.3 Ublox Driver
##### 3.3.1 Build Ublox Driver
1. To create a Workspace Directory, open a Terminal and create a folder (for example, **ros2_ws**) with a **src** subfolder:
```bash
mkdir -p ~/ros2_ws/src
```

2. Navigate to your workspace/src.
```bash
cd ~/ros2_ws/src
```

3. To clone the u-blox repository to your ROS 2 workspace
```bash
git clone --branch ros2 https://github.com/KumarRobotics/ublox.git
```

4. Initiate **rosdep** and download the latest package dependency definitions.
```bash
sudo rosdep init
rosdep update
```

5. To build u-blox Node, return to the main workspace folder and compile:
```bash
cd ~/ros2_ws
rosdep install --from-paths src --ignore-src -r -y
colcon build
source install/setup.bash
```

6. Now the u-blox Node is available in your ROS2 environment.
7. Modify the configuration file to update device paths or parameters as needed (we will use **/dev/ttyACM0** ). The ublox_gps package includes a default configuration file named **zed_f9p.yaml**. Open the configuration file by command and modify the "device":
```bash
nano ~/ros2_ws/src/ublox/ublox_gps/config/zed_f9p.yaml
```

8. To configure the node with the **zed_f9p.yaml** settings, update the launch file. Open the file and add the following line to load the configuration:
```bash
nano ~/ros2_ws/src/ublox/ublox_gps/launch/ublox_gps_node-launch.py
```

9. Rebuild the packages. We recommend using a **separate package** for your custom config and launch files to keep things organized. We’ll discuss that approach later.
```bash
cd ~/ros2_ws
colcon build
```

##### 3.3.2 test the GPS
```bash
source install/setup.bash
ros2 launch ublox_gps ublox_gps_node-launch.py
```
If everything is configured correctly, the node should begin publishing GPS data from the ttyACM0 receiver.

##### 3.3.3 topics and service list
1. Run the following command to view available Topics. Look for topics like **/ublox_gps_node/fix**, which contains GPS data in sensor_msgs/NavSatFix format, etc
```bash
ros2 topic list
```

2. View the list of available services provided by the Node.
```bash
ros2 service list
```

## 3.4 NTRIP Client
##### 3.4.1 Build NTRIP Client
1. Navigate to ROS2 workspace directory and clone the ROS 2 branch
```bash
cd ~/ros2_ws/src
git clone --branch ros2 https://github.com/LORD-MicroStrain/ntrip_client.git
```
2. Return to the workspace root, install any missing dependencies, and build the package
```bash
cd ~/ros2_ws
rosdep install --from-paths src --ignore-src -r -y
colcon build
```
3. Update NTRIP parameters such as host, port, username, password, and mountpoint and save the changes in file.
```bash
nano ~/ros2_ws/src/ntrip_client/launch/ntrip_client_launch.py
```

4. Rebuild
```markup
cd ~/ros2_ws
colcon build
```

##### 3.4.2 Test NTRIP Client
1. Launch the Node with your NTRIP parameters to establish a connection to the NTRIP Caster:
```bash
ros2 launch ntrip_client ntrip_client_launch.py
```
##### 3.4.3 Topics and services list
```bash
ros2 topic list
ros2 service list
```
## 3.5 Test RTK
1. Check node connection
```bash
rqt_graph
```
2. Check topics
open three terminal under the workspace, and `source install/setup.bash` each terminal. Check the /nmea, /rtcm and /ublox_gps_node/navpvt separately in the terminals

there are a lot of data format in the nmea to represent the RTK status. GxGGA will be used in this instruction.
```bash
ros2 topic echo /nmea | grep GGA
```
the 7th bit of the GGA in the /nmea represent the RTK status. The following list shows the meaning of all GGA's bits.



```bash
ros2 topic echo /rtcm
```
The rtcm should have message

```bash
ros2 topic echo /ublox_gps_node/navpvt
```
In the /ublox_gps_node/navpvt, the fix_type and flags represent the GPS and RTK localization status as Table below shows.

## 3.6 Current RTK localization results and issues
##### 3.6.1 Current RTK localization results
I did two tests on campus. 

###### 3.6.2 Current issues
1. The RTK localization will fail down when the movement is too fast.
2. The RTK cannot get the fix status. 

## 3.7 Possible Solution
1. We have asked the Sparkfun for technical support
2. We will try the Wheeltech N100 RTK localization system as an alternative. 