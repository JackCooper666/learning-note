1. check your gcc and g++ version by
```bash
gcc -v
g++ -v
```

2. check whether you already have the nvidia driver by using or checking the "Additional Drivers" in the software&update. 
```bash
nvidia-smi
```
you may get something like this, if you download the driver already, the "**CUDA version**" is the **maximal version** which is compatible with your current driver
```bash
Tue May 13 15:05:21 2025       
+-----------------------------------------------------------------------------------------+
| NVIDIA-SMI 570.133.07             Driver Version: 570.133.07     CUDA Version: 12.8     |
|-----------------------------------------+------------------------+----------------------+
| GPU  Name                 Persistence-M | Bus-Id          Disp.A | Volatile Uncorr. ECC |
| Fan  Temp   Perf          Pwr:Usage/Cap |           Memory-Usage | GPU-Util  Compute M. |
|                                         |                        |               MIG M. |
|=========================================+========================+======================|
|   0  NVIDIA GeForce GTX 1650        Off |   00000000:01:00.0  On |                  N/A |
| N/A   43C    P8              6W /   50W |     624MiB /   4096MiB |      6%      Default |
|                                         |                        |                  N/A |
+-----------------------------------------+------------------------+----------------------+
                                                                                         
+-----------------------------------------------------------------------------------------+
| Processes:                                                                              |
|  GPU   GI   CI              PID   Type   Process name                        GPU Memory |
|        ID   ID                                                               Usage      |
|=========================================================================================|
|    0   N/A  N/A            1669      G   /usr/lib/xorg/Xorg                      235MiB |
|    0   N/A  N/A            1831      G   /usr/bin/gnome-shell                     37MiB |
|    0   N/A  N/A            3450    C+G   warp-terminal                            47MiB |
|    0   N/A  N/A            9073      G   /opt/google/chrome/chrome                 1MiB |
|    0   N/A  N/A            9121      G   ...ersion=20250512-050045.427000         51MiB |
|    0   N/A  N/A            9383      G   .../4848/usr/lib/firefox/firefox        186MiB |
|    0   N/A  N/A           14961      G   ...ess --variations-seed-version         50MiB |
+-----------------------------------------------------------------------------------------+
```

3. download the toolkit by **runfile**
	It will ask you two questions
		1. whether remove your current driver
			if your driver can handle the cuda, please select **"continue"**
		2. whether install a new driver
			if you select **"continue"**, please do not tick the **"new driver"**
	**warning:** if you already have the nvidia driver. please do not
4. added the path of your toolkit in .bashrc like these lines
```bashrc
export PATH=/usr/local/cuda-12.5/bin${PATH:+:${PATH}}
export LD_LIBRARY_PATH=/usr/local/cuda-12.5/lib64\
                         ${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
```

