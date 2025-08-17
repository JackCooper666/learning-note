in the ~/.bashrc file
activate the conda and deactivate the ros noetic
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

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/arc/.conan/data/gflags/2.2.2/_/_/package/88539f002769027b252fd7a108dc2f1fa9529154/lib
export LIBRARY_PATH=$LIBRARY_PATH:/home/arc/.conan/data/gflags/2.2.2/_/_/package/88539f002769027b252fd7a108dc2f1fa9529154/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/arc/.conan/data/glog/0.6.0/_/_/package/a9d362b17f05cef8580ca68487c6299654e427f6/lib
export LIBRARY_PATH=$LIBRARY_PATH:/home/arc/.conan/data/glog/0.6.0/_/_/package/a9d362b17f05cef8580ca68487c6299654e427f6/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/arc/.conan/data/ceres-solver/1.14.0/_/_/package/7195fd60b8544268e80a4a2edca60ab3e55f8aa9/lib
export LIBRARY_PATH=$LIBRARY_PATH:/home/arc/.conan/data/ceres-solver/1.14.0/_/_/package/7195fd60b8544268e80a4a2edca60ab3e55f8aa9/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/arc/.conan/data/osqp/0.6.3/_/_/package/2af715f34a7c8c2aeae57b25be0a52c4110dc502/lib


export LIBRARY_PATH=$LIBRARY_PATH:/home/arc/.conan/data/osqp/0.6.3/_/_/package/2af715f34a7c8c2aeae57b25be0a52c4110dc502/lib
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/arc/.conan/data/libunwind/1.8.0/_/_/package/c8c888b1fc83f5e0145e8890c2af3bd4e0005c98/lib
export LIBRARY_PATH=$LIBRARY_PATH:/home/arc/.conan/data/libunwind/1.8.0/_/_/package/c8c888b1fc83f5e0145e8890c2af3bd4e0005c98/lib

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

download the project
```git
git clone https://github.com/muskie82/MonoGS.git
```
then cd to the MonoGS project
```bash
cd MonoGS
```
create environment
```bash
conda create -n MonoGS python=3.8
conda activate MonoGS
conda install -y -c nvidia/label/cuda-11.6.0 cuda-toolkit=11.6
pip install -r requirement.txt
export PYTHONNOUSERSITE=1
unset PYTHONPATH
conda install -y -c pytorch -c conda-forge   pytorch==1.12.1 torchvision==0.13.1 torchaudio==0.12.1 cudatoolkit=11.6
```

the requirement.txt is the following
```txt
--extra-index-url https://download.pytorch.org/whl/cu116

# PyTorch (CUDA 11.6 wheels)
torch==1.12.1+cu116
torchvision==0.13.1+cu116
torchaudio==0.12.1+cu116

# Core libs
numpy==1.23.5
plyfile==0.8.1
tqdm

# Project deps
opencv-python==4.8.1.78
munch
trimesh
evo==1.11.0
open3d==0.17.0
torchmetrics==0.11.4
imgviz
PyOpenGL
glfw
PyGLM
wandb
lpips
rich
ruff

# Local CUDA extensions (editable install)
-e submodules/simple-knn
-e submodules/diff-gaussian-rasterization
```

download the TUM-RGBD dataset
```bash
bash scripts/download_tum.sh
```

train and visualize the TUM-RGBD dataset
```bash
python slam.py --config configs/mono/tum/fr3_office.yaml
```

then you may get this error
```bash
ImportError: Failed to import any of the following Qt binding modules: PyQt6, PySide6, PyQt5, PySide2
```
