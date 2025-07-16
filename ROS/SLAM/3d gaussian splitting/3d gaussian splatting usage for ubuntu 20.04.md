refer to: CSDN博主「世锦星河」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/maryu/article/details/142705866

refer to: CSDN博主「Sakuya__」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/Sakuya__/article/details/135376331
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
1. **deactivate** the conda environment
```bash
conda deactivate
```
2. install dependencies
```bash
sudo apt update
sudo apt install -y libglew-dev libassimp-dev libboost-all-dev libgtk-3-dev libopencv-dev libglfw3-dev libavdevice-dev libavcodec-dev libeigen3-dev libxxf86vm-dev libembree-dev
sudo apt install libglfw3-dev 
sudo apt install libavdevice-dev libavformat-dev libavcodec-dev libswscale-dev libavutil-dev  
```
3. switch git branch of the SIBR
```git
cd SIBR_viewers
git checkout fossa_compatibility
```
4. cmake link
```bash
cmake -Bbuild . -DCMAKE_BUILD_TYPE=Release
```
5. cmake compile
```bash
cmake --build build -j24 --target install
```

# Input dataset making
1. record a video in .mp4 format and save it in your_dataset_folder
2. use the ffmpeg under your_dataset_folder to cut the video into images, 
```bash
cd /to/your_folder
ffmpeg -i input.mp4 -vf "setpts=0.2*PTS" input/input_%4d.jpg
```
3. use the gaussian-splatting/convert.py to get the pcd by the colmap, so the colmap should be installed successfully before this step.
```bash
python convert.py -s /the/complete/path/to/your_dataset_folder
```
if colmap run successfully, you will get
```bash
your_folder
├── distorted
├── images
├── input
├── run-colmap-geometric.sh
├── run-colmap-photometric.sh
├── sparse
└── stereo
```

---
you may get such errors during colmap
```bash
E0715 15:04:47.457129 179607 option_manager.cc:923] Failed to parse options - unrecognised option '--SiftExtraction.use_gpu'. ERROR:root:Feature extraction failed with code 256. Exiting.
```
and
```bash
E0715 15:04:47.457129 179607 option_manager.cc:923] Failed to parse options - unrecognised option '--SiftMatching.use_gpu'. ERROR:root:Feature extraction failed with code 256. Exiting.
```
This is because you're using a newer version of COLMAP where these parameters have been changed or removed

Solution:
Just commend out the two parameters in the convert.py like
```python
## Feature extraction
feat_extracton_cmd = colmap_command + " feature_extractor "\
"--database_path " + args.source_path + "/distorted/database.db \
--image_path " + args.source_path + "/input \
--ImageReader.single_camera 1 \
--ImageReader.camera_model " + args.camera + " \
# --SiftExtraction.use_gpu " + str(use_gpu)
exit_code = os.system(feat_extracton_cmd)
if exit_code != 0:
logging.error(f"Feature extraction failed with code {exit_code}. Exiting.")
exit(exit_code)

## Feature matching
feat_matching_cmd = colmap_command + " exhaustive_matcher \
--database_path " + args.source_path + "/distorted/database.db \
# --SiftMatching.use_gpu " + str(use_gpu)
exit_code = os.system(feat_matching_cmd)
if exit_code != 0:
logging.error(f"Feature matching failed with code {exit_code}. Exiting.")
exit(exit_code)
```
# Evaluation
1. train, the training result will be stored in a folder named randomly under the gaussian_splatting/output 
```bash
python train.py -s /the/complete/path/of/your_dataset_folder
```
2.  render
```bash
python render.py -m /the/complete/path/of/the_folder_storing_the_result
```
such as `/home/gaussian-splatting/output/ef3605e3-d`
2. error evaluation
```bash
python metrics.py -m /the/complete/path/of/the_folder_storing_the_result
```
# Visualization
go to the gaussian-splatting/SIBER_viewers/install/bin
```bash
./SIBR_gaussianViewer_app -m /the/complete/path/of/the_folder_storing_the_result
```