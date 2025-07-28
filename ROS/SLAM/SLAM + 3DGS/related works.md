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
We utilize our LM implementation in the second stage of3DGS optimization (see Fig. 2). Before that, we use the ADAM optimizer to obtain an initialization of the Gaussian parameters. It is also possible to use the LM optimizer from the beginning, however this does not bring any additional speed-up (see Fig. 4). In the beginning of optimization, gradient descent makes rapid progress by optimizing the Gaussians from a single image per iteration. In contrast, we sample many images in every LM iteration, which makes every iteration more time-consuming. This additional compute overhead is especially helpful to converge to optimal Gaussian parameters quicker (see Fig. 1 left). Splitting the method in two stages also allows us to complete the densification of the Gaussians before employing the LM optimizer, which simplifies the implementation.

# DashGaussian
这篇文章《DashGaussian: Optimizing 3D Gaussian Splatting in 200 Seconds》提出了一种名为DashGaussian的方法，旨在加速3D高斯泼溅（3D Gaussian Splatting, 3DGS）的优化过程，同时保持渲染质量。以下是其核心原理的详细解释：

---

## 1. **问题背景**

3D高斯泼溅（3DGS）是一种用于新视角合成的技术，通过优化一组3D高斯基元来表示场景。然而，3DGS的优化过程通常需要较高的计算成本，尤其是在高分辨率渲染和高斯基元数量较多时。现有的加速方法（如剪枝冗余基元或优化渲染管线）往往以牺牲渲染质量为代价。

## 2. **核心思想**

DashGaussian的核心思想是通过动态调度优化复杂度（包括渲染分辨率和高斯基元数量）来合理分配计算资源，从而在不降低渲染质量的前提下加速优化。具体来说：

- **动态渲染分辨率**：在优化初期使用低分辨率图像，逐渐过渡到高分辨率，以减少计算量。
- **基元数量调度**：根据渲染分辨率动态调整高斯基元的数量，避免过度密集化。
---

## 3. **技术原理**

### 3.1 **优化复杂度的定义**

优化复杂度由两个主要因素决定：
1. **渲染分辨率**：分辨率越高，计算量越大。
2. **高斯基元数量**：基元越多，计算负担越重。
DashGaussian通过动态调整这两个因素来降低整体优化复杂度。

### 3.2 **频率引导的分辨率调度**

- **频率理论**：图像的高频分量对应细节信息，低频分量对应整体结构。低分辨率图像缺少高频分量，因此优化初期可以用低分辨率图像拟合低频信息，后期再用高分辨率图像补充高频细节。
- **分辨率调度**：
    - 通过计算训练视图的频率能量（公式2），动态决定何时从低分辨率切换到高分辨率。
    - 使用分数函数（公式3）分配优化步骤，确保高分辨率阶段仅在必要时使用。
### 3.3 **分辨率引导的基元调度**

- **基元数量与分辨率的关系**：高分辨率需要更多基元来描述细节，而低分辨率时基元过多会导致计算冗余。
- **基元增长曲线**：
    - 基元数量随优化步骤动态调整（公式4），初期增长缓慢，中期加速，后期趋于稳定。
    - 采用凹向上的增长曲线，减少早期计算量。
- **动量基元预算**：
    - 动态估计最终基元数量（公式5），避免依赖经验值。
    - 通过动量更新机制（类似物理中的动量）自适应调整基元数量。

### 3.4 **抗锯齿与优化质量**

- 低分辨率训练时，采用抗锯齿下采样避免误导优化。
- 通过渐进式增加分辨率，逐步拟合高频分量，避免3D走样问题。

---

## 4. **实现细节**

1. **分辨率调制**：将连续的分辨率因子离散化，以简化计算。
2. **学习率调整**：在低分辨率阶段保持较高的学习率，高分辨率阶段逐步衰减。
3. **基元剪枝与分裂**：根据基元的梯度或渲染误差动态剪枝或分裂基元，控制基元数量。



# GauSS-MI
This paper introduces Gaussian Splatting Shannon Mutual Information (GauSS-MI) as a metric for efficient next best view selection in high-visual fidelity active reconstruction.

