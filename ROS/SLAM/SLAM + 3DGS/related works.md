# Gaussian-lic
key steps:
1. initialization of gaussian map
	The photo-realistic Gaussian map is bootstrapped with all 3D points of the first received frame.
2. expansion the gaussian map
	Every frame after the first usually captures the geometry and appearance of the newly observed areas. However, LiDAR points from different frames may contain duplicate information. We take every fifth frame as a keyframe. When a keyframe is received, we first merge all points received in these five frames into a point cloud. To avoid redundancy, we then render O from the current keyframe image view according to α-blending.
3. optimize the gaussian map
	Once the current received frame is a keyframe, we randomly select K keyframes from all keyframes to optimize the Gaussian map, avoiding the catastrophic forgetting problems and maintaining the geometric consistency of the global map. We randomly shuffle the selected K keyframes and iterate through each of them to optimize the map by minimizing re-rendering loss:
$$
L = (1 - \lambda )\left \| E[C] - \bar{C}  \right \|_{1} + \lambda L_{D-SSIM} 
$$

CUDA multi thread backpropagation
1. perform per-Gaussian back-propagation and assign CUDA threads for all Gaussians in a tile, increasing the parallelism while decreasing collisions.
2. For faster training of the Gaussianmap representation, sparse Adamwas applied to only update Gaussians in the current camera frustum.
3. remove slim gaussian balls

# GS-LIVO
1. The lio will do the IESKF to get the state estimation
2. the gaussian initialize the gaussian balls according to the current image and lidar point cloud at t he estimated state
3. the gaussian balls will be put into the global gaussian map (octree similar with the voxel map) to filter out the useless and invalid points
4. the filtered gaussian balls in current frame will be put into the sliding window and be optimized
5. the lio state estimation and the optimized gaussian balls and image in current frame will be put into the vio part to do the state estimation

# 3DGS-LM -> only to improve the 3d gaussian, not  the slam
We utilize our LM implementation in the second stage of
3DGS optimization (see Fig. 2). Before that, we use the
ADAM optimizer to obtain an initialization of the Gaussian
parameters. It is also possible to use the LM optimizer from
the beginning, however this does not bring any additional
speed-up (see Fig. 4). In the beginning of optimization,
gradient descent makes rapid progress by optimizing the
Gaussians from a single image per iteration. In contrast, we
sample many images in every LM iteration, which makes
every iteration more time-consuming. This additional com-
pute overhead is especially helpful to converge to optimal
Gaussian parameters quicker (see Fig. 1 left).
Splitting the method in two stages also allows us to com-
plete the densification of the Gaussians before employing
the LM optimizer, which simplifies the implementation.


