# 0. Clone the repository
```bash
git clone https://github.com/PRBonn/PINGS.git --recursive
cd PINGS
```

# 1. Set up conda environment
```conda
conda create --name pings python=3.10
conda activate pings
```

# 2. install dependencies
the 
submodules/diff-gaussian-surfel-rasterization-w-pose
submodules/fused-ssim
submodules/diff-gaussian-rasterization-w-pose
are empty, please download them from the github
```git
git clone https://github.com/rmurai0610/diff-gaussian-rasterization-w-pose.git

git clone https://github.com/YuePanEdward/diff-gaussian-surfel-rasterization-w-pose.git

git clone https://github.com/rahul-goel/fused-ssim.git
```


```bash
# 1) install the cuda 11.8 in conda env
conda install -c "nvidia/label/cuda-11.8.0" cuda-toolkit

# 2) 确保用的是 env 里的 nvcc；并把 CUDA_HOME 正确指到当前 env
conda env config vars set CUDA_HOME="$CONDA_PREFIX" CUDACXX="$CONDA_PREFIX/bin/nvcc" TORCH_CUDA_ARCH_LIST="8.6"
conda deactivate && conda activate pings

# check the path of nvcc, the nvcc should be under the current env
which nvcc
nvcc --version


# 3) 安装 PyTorch cu118 官方 wheel
python -m pip install --upgrade pip
python -m pip install \
  torch==2.4.1+cu118 torchvision==0.19.1+cu118 torchaudio==2.4.1+cu118 \
  --index-url https://download.pytorch.org/whl/cu118

# check the torch and cuda
python - <<'PY'                                
import os, torch
print("torch:", torch.__version__)
print("torch.version.cuda:", torch.version.cuda)
print("cuda.is_available:", torch.cuda.is_available())
print("CUDA_HOME:", os.environ.get("CUDA_HOME"))
if torch.cuda.is_available():
    print("GPU:", torch.cuda.get_device_name(0))
from torch.utils.cpp_extension import CUDA_HOME
print("cpp_extension.CUDA_HOME:", CUDA_HOME)
PY

# 4) install dependencies
python -m pip install -U setuptools wheel ninja
  
# 4) install the glm
conda install -y -c conda-forge glm

# 5) install gcc and g++ 11.4
conda install -n pings -c conda-forge gcc=11 gxx=11
# please check the location of the gcc and g++
which gcc
which g++

# 6) install 
python -m pip install -r requirements.txt

```
# 3. dataset making
# 4. run
