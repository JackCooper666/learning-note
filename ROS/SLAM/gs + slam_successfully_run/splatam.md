create the conda environment
```bash
conda create -n splatam python=3.10
conda activate splatam
conda install -c "nvidia/label/cuda-11.6.0" cuda-toolkit
conda install pytorch==1.12.1 torchvision==0.13.1 torchaudio==0.12.1 cudatoolkit=11.6 -c pytorch -c conda-forge
pip install -r requirements.txt
```

but the `requirements.txt` is wrong, the torchmetrics does not match the `diff-gaussian-rasterization`, the 
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
