# Prerequisites
1. ensure the nvidia driver is installed
```bash
nvidia-smi
```

2. ensure you already have a version of cuda toolkit
```bash
nvcc --version
```

# Install cuda toolkit
When install cuda toolkit please use the runfile
this is the cuda 11.7 installation by runfile
``` bash
wget https://developer.download.nvidia.com/compute/cuda/11.7.0/local_installers/cuda_11.7.0_515.43.04_linux.run

sudo sh cuda_11.7.0_515.43.04_linux.run
```


# Build symlink
direct to you /usr/local
```bash
sudo rm -rf cuda #if you have old symlink
sudo ln -s /usr/local/cuda-11.6 /usr/local/cuda
```

# Adjust the bashrc
put this in the bashrc to include the symlink in the global environment

```bash
#在bashrc末尾添加(如下图)
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/cuda/lib64
export PATH=$PATH:/usr/local/cuda/bin
export CUDA_HOME=$CUDA_HOME:/usr/local/cuda
```

