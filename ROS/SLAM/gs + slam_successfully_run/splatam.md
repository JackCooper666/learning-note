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
git clone https://github.com/spla-tam/SplaTAM.git
```

create the conda environment
```bash
conda create -n splatam python=3.10
conda activate splatam
conda install -c "nvidia/label/cuda-11.6.0" cuda-toolkit
conda install pytorch==1.12.1 torchvision==0.13.1 torchaudio==0.12.1 cudatoolkit=11.6 -c pytorch -c conda-forge
pip install -r requirements.txt
```

but the original `requirements.txt` is wrong, the torchmetrics does not match the `diff-gaussian-rasterization`, and the numpy does not match as well.

this one is correct.
```txt
tqdm==4.65.0
numpy==1.23.5          # safe with torch 1.12.x and many older wheels
torchmetrics==0.11.4   # last series that supports torch 1.x well
Pillow
opencv-python
imageio
matplotlib
kornia
natsort
pyyaml
wandb
lpips
open3d==0.16.0
cyclonedds
pytorch-msssim
plyfile==0.8.1
git+https://github.com/JonathonLuiten/diff-gaussian-rasterization-w-depth.git@cb65e4b86bc3bd8ed42174b72a62e8d3a3a71110
```

then cd to the SplaTAM and download the TUM-RGBD dataset
```bash
bash bash_scripts/download_tum.sh
```

then change the use_wandb = True to False in the configs/tum/splatam.py

then start to train
```python
python scripts/splatam.py configs/tum/splatam.py
```

visualize the result
```python
python viz_scripts/final_recon.py configs/tum/splatam.py
```
