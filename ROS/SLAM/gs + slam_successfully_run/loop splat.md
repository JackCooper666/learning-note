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
git clone --recursive git@github.com:GradientSpaces/LoopSplat.git
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
conda create -n loop_splat -c nvidia/label/cuda-12.1.0 cuda=12.1 cuda-toolkit=12.1 cuda-nvcc=12.1
conda env update --file environment.yml --prune
conda activate loop_splat
pip install -r requirements.txt
```
Please use the following environment.yaml and requirements.txt
```yaml
name: loop_splat
channels:
  - pytorch
  - nvidia
  - nvidia/label/cuda-12.1.0
  - conda-forge
  - defaults
dependencies:
  - python=3.10
  - faiss-gpu=1.8.0
  - cuda-toolkit=12.1
  - pytorch=2.1.2
  - pytorch-cuda=12.1 
  - torchvision=0.16.2
  - pip
  - pip:
      - open3d==0.18.0
      - wandb
      - trimesh==4.0.10
      - pytorch_msssim
      - torchmetrics
      - tqdm
      - imageio
      - opencv-python
      - plyfile
      - roma
      - einops==0.8.0
      - numpy==1.26.4
      - PyQt5==5.15.11
      - matplotlib==3.5.1
      - evo==1.11.0
      - python-pycg
      - einops
      - git+https://github.com/eriksandstroem/evaluate_3d_reconstruction_lib.git@9b3cc08be5440db9c375cc21e3bd65bb4a337db7
      - git+https://github.com/VladimirYugay/simple-knn.git@c7e51a06a4cd84c25e769fee29ab391fe5d5ff8d
      - git+https://github.com/VladimirYugay/gaussian_rasterizer.git@9c40173fcc8d9b16778a1a8040295bc2f9ebf129
      - git+https://github.com/rmurai0610/diff-gaussian-rasterization-w-pose.git@43e21bff91cd24986ee3dd52fe0bb06952e50ec7
```

```txt
open3d==0.18.0
wandb
trimesh==4.0.10
pytorch_msssim
torchmetrics
tqdm
imageio
opencv-python
plyfile
roma
einops==0.8.0
numpy==1.26.4
PyQt5==5.15.11
matplotlib==3.5.1
evo==1.11.0
python-pycg
einops
git+https://github.com/VladimirYugay/simple-knn.git@c7e51a06a4cd84c25e769fee29ab391fe5d5ff8d
git+https://github.com/eriksandstroem/evaluate_3d_reconstruction_lib.git@9b3cc08be5440db9c375cc21e3bd65bb4a337db7
git+https://github.com/VladimirYugay/gaussian_rasterizer.git@9c40173fcc8d9b16778a1a8040295bc2f9ebf129
git+https://github.com/rmurai0610/diff-gaussian-rasterization-w-pose.git@43e21bff91cd24986ee3dd52fe0bb06952e50ec7
```

in your /thridparty, remove the original /Hierarchical-Localization, use this one
```bash
git clone --recursive https://github.com/cvg/Hierarchical-Localization/
cd Hierarchical-Localization/
python -m pip install -e .
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
# visualization