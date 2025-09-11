this installation instruction in under the cuda 11.8
this is environment yaml file to build the conda environment
```yaml
name: point-slam
channels:
  - conda-forge      # 放最前，避免 toolchain 冲突
  - pytorch
  - nvidia
  - defaults
dependencies:
  # 基础
  - python=3.10
  - pip

  # PyTorch + CUDA 11.8 运行时
  - pytorch=2.3.*
  - torchvision=0.18.*
  - torchaudio=2.3.*
  - pytorch-cuda=11.8        # 来自 nvidia
  - cuda-version=11.8        # 让其它 GPU 包与 11.8 对齐（conda-forge 约束）

  # 数值栈（用 conda 统一解算，避免 pip/ABI 冲突）
  - numpy>=1.26,<2
  - scipy>=1.11,<1.12
  - ffmpeg

  # FAISS（GPU 版，随 cuda-version 选择 cu118 变体）
  - faiss-gpu=1.7.4

  # 其余依赖尽量走 pip（不要在 pip 再装 numpy / faiss）
  - pip:
    - antlr4-python3-runtime==4.9.3
    - appdirs==1.4.4
    - attrs==22.1.0
    - autopep8==2.0.0
    - brotli==1.0.9
    - click==8.1.3
    - colorama==0.4.6
    - configargparse==1.5.3
    - contourpy==1.0.6
    - cycler==0.11.0
    - dash==2.6.2
    - dash-core-components==2.0.0
    - dash-html-components==2.0.0
    - dash-table==5.0.0
    - docker-pycreds==0.4.0
    - einops==0.5.0
    - fastjsonschema==2.16.2
    - flask==2.2.2
    - flask-compress==1.13
    - fonttools==4.38.0
    - gitdb==4.0.9
    - gitpython==3.1.29
    - hydra-core==1.3.2
    - imageio==2.22.2
    - itsdangerous==2.1.2
    - jinja2==3.1.2
    - joblib==1.2.0
    - jsonschema==4.16.0
    - jupyter-core==4.11.2
    - kiwisolver==1.4.4
    - lpips==0.1.4
    - markupsafe==2.1.1
    - mathutils==3.3.0
    - matplotlib==3.7.3
    - nbformat==5.5.0
    - networkx==2.8.7
    - omegaconf==2.3.0
    - open3d==0.16.0
    - opencv-python==4.6.0.66
    - packaging==21.3
    - pathtools==0.1.2
    - pillow==9.3.0
    - plotly==5.11.0
    - promise==2.3
    - protobuf==4.21.9
    - psutil==5.9.4
    - pycodestyle==2.9.1
    - pyparsing==3.0.9
    - pyrsistent==0.18.1
    - python-dateutil==2.8.2
    - pytorch-msssim==0.2.1
    - pywavelets==1.4.1
    - pyyaml==6.0
    - scikit-image==0.19.3
    - scikit-learn==1.1.3
    - sentry-sdk==1.10.1
    - setproctitle==1.3.2
    - shortuuid==1.0.10
    - smmap==5.0.0
    - snakeviz==2.1.1
    - tenacity==8.1.0
    - threadpoolctl==3.1.0
    - tifffile==2022.10.10
    - tomli==2.0.1
    - torch-fidelity==0.3.0
    - torchmetrics==0.11.1
    - tornado==6.2
    - tqdm==4.64.1
    - traitlets==5.5.0
    - trimesh==3.15.8
    - wandb==0.13.9
    - werkzeug==2.2.2

```

