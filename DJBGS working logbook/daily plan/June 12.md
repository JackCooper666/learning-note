- [x] fastlivo1 recorder update 1 hour
- [x] three questions leecode 2 hours
- [ ] find the reasons affect the fastlivo2 4hours
- [ ] phd apply 2 hours


fastlivo2 ac1 current issue:
- [ ] the result has some noise points compared with the rs-ac1-fastlivo
possible reasons
 1. the state estimation is not good
	1. lio estimation is not good, the imu params needs adjust (I do not think)
	2. the weight of the vio system state estimation is too high, vio system gives a wrong estimation to lio system in the next frame (I do not think, as the evo's rmse is 0.05, quite perfect)
 our:
![[arc3_fastlivo2_ac1.png]]
```bash
arc@arc-djb:~/zewen/enu_cal_plot/arc-fastlivo2-ac1_enu_res$ evo_ape tum arc3_gt.txt arc3_ac1_fastlivo2.txt --plot -a
APE w.r.t. translation part (m)
(with SE(3) Umeyama alignment)

   max      0.226360
  mean      0.050581
median      0.045843
   min      0.003653
  rmse      0.056793
   sse      2.496453
   std      0.025826
```
rs:
![[rs_arc3_fastlivo.png]]
```bash
arc@arc-djb:~/zewen/enu_cal_plot/rs-fastlivo-ac1-enu-res$ evo_ape tum arc3_gt.txt rs_fastlivo_traj.txt --plot -a
APE w.r.t. translation part (m)
(with SE(3) Umeyama alignment)

   max      0.178609
  mean      0.081629
median      0.079982
   min      0.007330
  rmse      0.088728
   sse      11.856240
   std      0.034777
```  
 
 2. lio system do not filter the noise clearly. (high possible)
 3. the vio system is not comprehensive. (high possible)