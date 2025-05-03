fastlivo2_ws:
->HK
->NTU 

r3live_ws: the direction of the gravity in the code was changed
-> HK
	-> rosbag play HKisland03.bag
	-> rosbag play HKairport01.bag -s 75 -r 0.5

r3live_velodynes_ws: the direction of the gravity in the code was changed
-> NTU
-> HIlti 

srlivo_ws: 
-> NTU
-> HK
	-> HKaiport
		rosbag play HKairport01.bag -s 100 -r 0.5
	->HKisland
		rosbag play HKisland03.bag -s 50 -r 0.5


lvisam_6_imu_ws:
-> HK -> but it does not compatible with Livox avia

lvisam_our_ws:
->NTU  
	rosbag play eee_01.bag
