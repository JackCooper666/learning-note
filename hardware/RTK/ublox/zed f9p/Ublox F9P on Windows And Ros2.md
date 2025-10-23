This is an instruction to demenstrate how to integrate ublox f9p with windows and ros2 step by step
# 1. Equipment overview
this is the overview of the equipment.



# 2. Windows
The RTK localization includes two parts: the GPS localization, and the NTRIP localization correction. This section will present a detailed instruction for achieving the RTK localization on Windows. 
## 2.1 Download U-center
1. Please, use the following link to download the u-center
	https://www.u-blox.com/en/product/u-center
2. In the Web page, please choose the u-center (highlighted by red box) not the u-center 2.
## 2.2 Connect the GPS
**Steps:**
1. Click the Receiver -> Connection to choose the serial port of the ublox as Figure below.
2. Then, set the baudrate of the serial communication. 
3.  Make sure the connection icon is flashing in the bottom status bar. This indicates that the serial communication between the computer and the GNSS device is working.
## 2.3 Verification the GPS connection and situation
The GPS testing need to be executed at empty outdoor environment. When the Fix mode on the right side of the interface shows 3D (green), it means that the right side is working normally, as Figure shows
## 2.4 Connect the NTRIP Client
**Steps:**
1. Make Sure your PC connects with internet. The personal Hotspot is recommended Because, the NTRIP access will be rejected by the Firewall sometime.  
2. Click the Receiver-> NTRIP Client, then key your host, port, username and password like the following Figure shows
3. Click the "Update source table," which will search the valid mount points, then choose your mount point. According to our previous test, the RTK_SiReNT_32 can provide an accurate localization result.
4. If the connection is successful, the ntrip connection icon will be green in the bottom status bar.
## 2.5 Check the RTK status
The RTK status should be tested under empty outdoor environment. The RTK status will be shown at the last word of the  Fix Mode like the followings Figures. The "Fix" in Figure means the RTK status is fix, the "Float" in Figure means the RTK status is float.


In addition, this figure is our test result of RTK status by Xsens mti 680g. Please have a look, as reference. The green points are RTK fix status, the orange points are RTK float status, and the red points are RTK invalid status.


## 2.6 Insert the google map
Meanwhile, the u-center can show the RTK localization result on the google map in real-time, like Figure.

**Prerequisites**
1. register a google map static map API through the following link

**Steps:**
1. input your google map static API at Tool->Preferences->Access Tokens, then click "Apply", then "OK"
2. open the "Map View" 
# 3. ROS2
## 3.1 Pre-setting on U-center
The Pre-setting on u-center includes two parts: the serial communication setting and the output messages setting.
##### Serial communication setting
**Steps:**
1. config the port under **menu bar  -> View -> Message View -> UBX -> CFG -> PRT (Ports)** like following Figure
2. Output frequency configuration under **menu bar  -> View -> Message View -> UBX -> CFG -> RATE(Rates)** like following Figure
3. After the modification is completed, finally choose to save the parameters under the **menu bar  -> View -> Message View -> UBX -> CFG -> CFG(Configuration)** like following Figure
##### Output messages setting
**Steps:**
1. Configure the receiver to output raw data and navigation messages

2. Configure the receiver to output navigation results in UBX format

3. Configure the receiver to output NMEA protocol related statements

4. After the modification is completed, finally choose to save the parameters under the **menu bar  -> View -> Message View -> UBX -> CFG -> CFG(Configuration)** like following Figure


## 3.2 Ublox driver

## 3.3NTRIP Client
## 3.4 Current issue
