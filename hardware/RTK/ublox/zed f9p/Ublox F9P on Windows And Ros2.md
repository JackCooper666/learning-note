This is an instruction to demenstrate how to integrate ublox f9p with windows and ros2 step by step
# 1. Equipment overview
this is the overview of the equipment.



# 2. Windows
The RTK localization includes two parts: the GPS localization, and the NTRIP localization correction. This section will present a detailed instruction for achieving the RTK localization on Windows. 
## 2.1 Connect the GPS
Steps:
1. Please, use the following link to download the u-center
	https://www.u-blox.com/en/product/u-center
2. In the Web page, please choose the u-center (highlighted by red box) not the u-center 2.
3. Click the Receiver -> Connection to choose the serial port of the ublox as Figure below.
4. Then, set the baudrate of the serial communication. 
5.  Make sure the connection icon is flashing in the bottom status bar. This indicates that the serial communication between the computer and the GNSS device is working.
## 2.2 Verification the GPS connection and situation
The GPS testing need to be executed at empty outdoor environment. If the GPS can do the localization, the Fix Mode should be  
## 2.3 Connect the NTRIP Client
## 2.4 Verification the NTRIP Client

# 3. ROS2
