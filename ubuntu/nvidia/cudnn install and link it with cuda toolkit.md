go to the link to find your required cudnn. Note that, the version of cuda toolkit should match correct cudnn 
https://developer.nvidia.com/cudnn-archive

get cuda toolkit 11.8 with cuDNN 9.10.2 as an example
```bash
wget https://developer.download.nvidia.com/compute/cudnn/9.10.2/local_installers/cudnn-local-repo-ubuntu2004-9.10.2_1.0-1_amd64.deb

sudo dpkg -i cudnn-local-repo-ubuntu2004-9.10.2_1.0-1_amd64.deb

sudo cp /var/cudnn-local-repo-ubuntu2004-9.10.2/cudnn-*-keyring.gpg /usr/share/keyrings/sudo apt-get update

sudo apt-get -y install cudnn
```

To install for CUDA 11, perform the above configuration but install the CUDA 11 specific package:

```bash
sudo apt-get -y install cudnn-cuda-11
```

Then you may get error like this
```bash
arc@arc-djb:~$ sudo apt-get -y install cudnn-cuda-11
Reading package lists... Done
Building dependency tree       
Reading state information... Done
Note, selecting 'cudnn9-cuda-11' instead of 'cudnn-cuda-11'
Some packages could not be installed. This may mean that you have
requested an impossible situation or if you are using the unstable
distribution that some required packages have not yet been created
or been moved out of Incoming.
The following information may help to resolve the situation:

The following packages have unmet dependencies: cudnn9-cuda-11 : Depends: cudnn9-cuda-11-8 (>= 9.10.2.21) but it is not going to be installed
E: Unable to correct problems, you have held broken packages.
```

that means the Depends: cudnn9-cuda-11-8 (>= 9.10.2.21) is not going to be installed, so install it and related dependencies by
```bash
# Install cuDNN 9 (CUDA 11) runtime + headers + dev
sudo apt install -y \
  /var/cudnn-local-repo-ubuntu2004-9.10.2/libcudnn9-cuda-11_9.10.2.21-1_amd64.deb \
  /var/cudnn-local-repo-ubuntu2004-9.10.2/libcudnn9-headers-cuda-11_9.10.2.21-1_amd64.deb \
  /var/cudnn-local-repo-ubuntu2004-9.10.2/libcudnn9-dev-cuda-11_9.10.2.21-1_amd64.deb
```

# uninstall the cudnn
find all cudnn packages
```bash
sudo dpkg -l | grep cudnn
```
uninstall all packages


**Note that**: the opencv 4.7.0 matches the cudnn 8.x 

