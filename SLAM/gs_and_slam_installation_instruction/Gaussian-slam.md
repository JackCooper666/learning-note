in the ~/.bashrc file, add this to switch between conda and ros
```bash
# >>> cuda toolkit >>>
export PATH=/usr/local/cuda/bin${PATH:+:${PATH}}
export LD_LIBRARY_PATH=/usr/local/cuda/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
# <<< cuda toolkit <<<

# >>> ros noetic >>>
echo "-----------------------------------------"
echo "Do you want to open ros noetic? (y/n)"
read -r input
if [[ "$input" =~ ^([yY][eE][sS]|[yY])$ ]]; then
        source /opt/ros/noetic/setup.bash
        echo "ros noetic activate"
else
        echo "skip ros noetic"
        unset PYTHONPATH
fi
# <<< ros noetic <<<

# >>> conda initialize >>>
# !! Contents within this block are managed by 'conda init' !!
echo "----------------------------------------"
echo "Do you want to initialize Conda? (y/n)"
read -r response
if [[ "$response" =~ ^([yY][eE][sS]|[yY])$ ]]; then
        __conda_setup="$('/home/arc/anaconda3/bin/conda' 'shell.bash' 'hook' 2> /dev/null)"
        if [ $? -eq 0 ]; then
            eval "$__conda_setup"
        else
                if [ -f "/home/arc/anaconda3/etc/profile.d/conda.sh" ]; then
                        . "/home/arc/anaconda3/etc/profile.d/conda.sh"
                else
                        export PATH="/home/arc/anaconda3/bin:$PATH"
                fi
        fi
        unset __conda_setup
        echo "Conda initialized. Use 'conda activate'."
else
        echo "Skipped Conda initialization." 
fi
# <<< conda initialize <<<
```

download the Gaussian-slam by the following link
```git
git clone https://github.com/VladimirYugay/Gaussian-SLAM
```

activate the conda and deactivate the ros noetic

Make sure that gcc and g++ paths on your system are exported:
```bash
which gcc
which g++
export CC=<gcc path>
export CXX=<g++ path>
```

```bash
conda env create -f environment.yml
conda activate gslam
```
the official environment.yaml is wrong, please use the following one
```yaml
name: gslam
channels:
	- pytorch
	- nvidia
	- conda-forge
	- defaults
dependencies:
	# Core
	- python=3.10
	- numpy=1.26.4
	# PyTorch CUDA 12.1 stack
	- pytorch=2.1.2
	- torchvision=0.16.2
	- pytorch-cuda=12.1 # don't add cuda-toolkit; this provides the runtime libs
	# Dev toolchain for CUDA extensions (nvcc + headers)
	- cuda-nvcc=12.1.105
	- cuda-cudart-dev=12.1.105
	- cuda-cccl=12.4.127 # CUB + libcudacxx + Thrust headers
	# Extras
	- faiss-gpu=1.8.0
	- ninja
	- pip
		- pip:
		- open3d==0.18.0
		- wandb
		- trimesh
		- pytorch_msssim
		- torchmetrics
		- tqdm
		- imageio
		- opencv-python==4.8.1.78
		- plyfile
		# use archives so git never prompts:
		-git+https://github.com/eriksandstroem/evaluate_3d_reconstruction_lib.git@9b3cc08be5440db9c375cc21e3bd65bb4a337db7
		- git+https://github.com/VladimirYugay/simple-knn.git@c7e51a06a4cd84c25e769fee29ab391fe5d5ff8d
		- git+https://github.com/VladimirYugay/gaussian_rasterizer.git@9c40173fcc8d9b16778a1a8040295bc2f9ebf129
```

# download the dataset (TUM_RBGD)
the official downloda_tum.sh is wrong, the downloaded package is incompleted, please replace the following one with the original download_tum.sh in the /scripts and use it by `bash /scripts/download_tum.sh`
```bash
mkdir -p data/TUM_RGBD
cd data/TUM_RGBD
wget https://vision.in.tum.de/rgbd/dataset/freiburg1/rgbd_dataset_freiburg1_desk.tgz
tar -xvzf rgbd_dataset_freiburg1_desk.tgz
wget https://cvg.cit.tum.de/rgbd/dataset/freiburg1/rgbd_dataset_freiburg1_desk2.tgz
tar -xvzf rgbd_dataset_freiburg1_desk2.tgz
wget https://cvg.cit.tum.de/rgbd/dataset/freiburg1/rgbd_dataset_freiburg1_room.tgz
tar -xvzf rgbd_dataset_freiburg1_room.tgz
wget https://vision.in.tum.de/rgbd/dataset/freiburg2/rgbd_dataset_freiburg2_xyz.tgz
tar -xvzf rgbd_dataset_freiburg2_xyz.tgz
wget https://vision.in.tum.de/rgbd/dataset/freiburg3/rgbd_dataset_freiburg3_long_office_household.tgz
tar -xvzf rgbd_dataset_freiburg3_long_office_household.tgz
```

# train
train a dataset
```bash
python run_slam.py configs/<dataset_name>/<config_name> --input_path <path_of_input_dataset> --output_path <output_path>
```

for example
```bash
python run_slam.py configs/TUM_RGBD/rgbd_dataset_freiburg1_desk.yaml --input_path data/TUM_RGBD/rgbd_dataset_freiburg1_desk --output_path output/TUM_RGBD/rgbd_dataset_freiburg1_desk/
```
