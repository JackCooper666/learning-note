go to the link to find your required cudnn. Note that, the version of cuda toolkit should match correct cudnn 
https://developer.nvidia.com/cudnn-archive

# install cuda toolkit 11.8 with cuDNN 9.10.2 
```bash
wget https://developer.download.nvidia.com/compute/cudnn/9.10.2/local_installers/cudnn-local-repo-ubuntu2004-9.10.2_1.0-1_amd64.deb

sudo dpkg -i cudnn-local-repo-ubuntu2004-9.10.2_1.0-1_amd64.deb

sudo cp /var/cudnn-local-repo-ubuntu2004-9.10.2/cudnn-*-keyring.gpg /usr/share/keyrings/

sudo apt-get update

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
## uninstall the cudnn 9.10.2 




# install cuda toolkit 11.7 with cudnn 8.9.7.29+cuda 11.8
take the cuda toolkit 11.7 and cudnn 8.9.7.29 as an example
go to this website to find the correct version of cudnn 

**Note that**: the opencv 4.7.0 matches the cudnn 8.x
the cudnn 8.9.7.29 is for cuda 11.8 but it matches the cuda 11.7 as well.

https://developer.nvidia.com/rdp/cudnn-archive


```bash
sudo dpkg -i cudnn-local-repo-ubuntu2004-8.9.7.29_1.0-1_amd64.deb

sudo cp /var/cudnn-local-repo-*/cudnn-local-*-keyring.gpg /usr/share/keyrings/
```

then install the the libcudnn8, libcudnn8-dev and libcudnn8-sample
```bash
sudo apt-get update
%% sudo apt-get install libcudnn8 libcudnn8-dev libcudnn8-samples %%
sudo apt-get install libcudnn8=8.9.7.29-1+cuda11.8
sudo apt-get install libcudnn8-dev=8.9.7.29-1+cuda11.8
sudo apt-get install libcudnn8-samples=8.9.7.29-1+cuda11.8
```

testing
```bash
cp -r /usr/src/cudnn_samples_v8/ $HOME
cd  $HOME/cudnn_samples_v8/mnistCUDNN
make clean && make
./mnistCUDNN
```
 

## uninstall the cudnn 8.9.7.29
find all cudnn packages
```bash
sudo dpkg -l | grep cudnn
```
uninstall all packages by
```bash
sudo apt remove --purge libcudnn8 libcudnn8-dev libcudnn8-samples
```



