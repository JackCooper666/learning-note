# Install
refer to https://github.com/graphdeco-inria/gaussian-splatting/issues/332
```bash
git clone https://github.com/graphdeco-inria/gaussian-splatting --recursive
```

CONDA ENVIRONMENT  
created the environment in conda using:  
`conda create -n gaussian_splatting python=3.7`

activated the environment  
`conda activate gaussian_splatting`

then installed the dependencies step by step
```bash
conda install pytorch==1.13.1 torchvision==0.14.1 torchaudio==0.13.1 pytorch-cuda=11.7 -c pytorch -c nvidia
pip install submodules/diff-gaussian-rasterization
pip install submodules/simple-knn  
pip install plyfile  
pip install tqdm
```
P.S. do not run the `conda env create --file environment.yml` or it breaks
# SIBER-VIWER install



# Train


# Evaluation