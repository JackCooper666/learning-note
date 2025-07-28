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

这篇文章《GauSS-MI: Gaussian Splatting Shannon Mutual Information for Active 3D Reconstruction》提出了一种基于高斯泼溅（3D Gaussian Splatting, 3DGS）和香农互信息（Shannon Mutual Information, SMI）的主动三维重建系统，旨在通过量化视觉不确定性并选择最优视角来提高重建效率和视觉质量。以下是其核心实现原理的详细介绍：
## 1. **问题背景与挑战**
- **主动三维重建**：在未知环境中，机器人需要动态选择下一个最佳视角（Next-Best-View, NBV）以高效完成高质量的三维重建。
- **现有问题**：传统方法主要关注几何完整性（如体素覆盖），而忽略视觉质量的不确定性量化，导致重建结果在纹理和细节上表现不佳。
- **新需求**：需要一种能够实时评估视觉信息增益的指标，并指导机器人选择信息量最大的视角。
## 2. **核心方法：GauSS-MI**

### （1）**概率模型构建**
- **高斯泼溅表示**：场景由多个3D高斯椭球体（Gaussians）表示，每个高斯包含几何（位置、协方差）和光学属性（颜色、透明度）。
- **可靠性概率**：为每个高斯定义一个二元随机变量 $r$，表示其渲染的可靠性（可靠或不可靠），初始化为无先验信息（$P(r) = 0.5$）。
- **逆传感器模型**：通过当前观测与渲染图像的损失（颜色和深度差异）更新高斯的可靠性概率。损失越小，可靠性越高：
	$$
	P(r^{i} | Z_{k}) = \frac{1} {(\lambda_{L}L_{k})^{\lambda_{T}T^{[i]}} + 1}
	$$
    其中 ​$L_{k}$ 是损失图像，$T^{[i]}$ 是高斯的累积透射率（调节更新强度）。
### （2）**香农互信息（GauSS-MI）**
- **目标**：量化从新视角 $z_{k}$​ 中获取的预期信息增益，以最小化地图的不确定性（条件熵）。
    
- **互信息定义**：
    
    $$I(r;z_{k})=H(r)−H(r∣z_{k})$$
    
    最大化互信息等价于最小化条件熵。
    
- **高效计算**：通过解析推导，将互信息分解为像素级信息增益的累加：
    $$
    I(r;z) = \sum_{j = 1}^{n_{z}}P(z^{[j]}|M^{[j]}) \sum_{i\in N^{[j]}}^{}-T^{[i]}log(P(r^{[i]}))
    $$
    
    其中 $P(z^{[j]})$ 是传感器测量先验（基于亮度噪声模型），$log⁡(P(r^{[i]}))$ 反映高斯的信息增益。
### （3）**实时性能优化**

- **并行化**：利用CUDA实现高斯投影和互信息计算的并行化，复杂度为 $O(N_{p}N_{g}N_{c})$，其中 $N_{p}$​ 是像素数，$N_{g}$​ 是高斯数，$N_{c}$​ 是候选视角数。
- **对比优势**：相比Fisher信息矩阵方法（复杂度随观测数量增长），GauSS-MI的计算量稳定，适合实时应用。
## **3. 系统架构总览**

系统分为两大模块：**在线3DGS重建模块**和**主动规划模块**，通过共享内存实现实时数据交互。

### **1. 在线3DGS重建模块**

#### **(1) 实时高斯泼溅地图构建**

- **初始化**：首帧RGB-D数据通过SFM（如COLMAP）或SLAM（如Gaussian Splatting SLAM）初始化高斯椭球体，属性包括：
    - 几何参数：均值 $\mu_{\omega}^{[i]}$​（世界坐标系位置）、协方差 $Σ_{W}^{[i]}$​（各向异性形状）。
    - 光学参数：球谐系数（颜色 $c^{[i]}$）、透明度 $α^{[i]}$。
- **动态扩展**：
    - 新观测的深度图通过**反投影**生成候选高斯，剔除冗余（基于重叠度阈值）。
    - 使用**梯度下降**在线优化高斯参数（每帧迭代10-20次），损失函数为RGB-D的L1损失 + SSIM：
        $$L_{total}=λ_{rgb}∥C−\hat{C}∥+λ_{depth}∥D−\hat{D}∥+λ_{ssim}SSIM(C,\hat{C})$$

#### **(2) 概率地图更新（Algorithm 1）**

- **输入**：当前帧的RGB-D图像 $\hat{C}_{k}$,$\hat{D}_{k}$​ 和相机位姿 $σ_{k}$​。
- **关键步骤**：
    1. **渲染与损失计算**：
        - 通过3DGS渲染当前视角的预测图像 $C,D$。
        - 计算逐像素损失 $$L_{k}=λ_{c}∥C−\hat{C}_{k}∥+(1−λ_{c})∥D−\hat{D}_{k}∥$$
            
    2. **概率反向投影**：
        - 对每个像素 $j$，沿射线排序高斯 $N^{[j]}$，计算累积透射率 $T^{[i]}$（公式3）。
        - 更新高斯的log odds（公式10）：
            $$l_{1:k}^{[i]}=−λ_{T}T^{[i]}log⁡(λ_{L}L_{k}^{[j]})+l_{1:k−1}^{[i]}$$​
    3. **概率转换**：通过sigmoid函数将log odds转为概率 $$P(r^{[i]}) = \frac{1}{1 + e^{-l^[i]}}$$
- **优化细节**：
    - 使用CUDA并行化射线追踪和概率更新，每个线程处理一条射线（像素）。
    - 内存管理：采用哈希表（如InstantNGP的网格结构）加速高斯查询。

### **2. 主动规划模块**

#### **(1) 候选视角生成（Viewpoint Primitive Library）**

- **动作空间设计**（公式21）：
    
    - 四旋翼的简化动作参数 α=$[v_{xy},v_{z},ω_{z}]$，离散化为：
        $V_{xy}={0,0.5,1.0} m/s,V_{z}={−0.2,0,0.2} m/s,Ω_{z}={−30^{\circ},0^{\circ},30^{\circ}}$
    - **前向传播**（公式22）：给定当前状态 $σ_{0}=[x_{0},y_{0},z_{0},ψ_{0}]^{T}$，生成终点状态 $σ_{f}$​（位置和偏航角）。
        
- **运动基元（Motion Primitive）**：
    
    - 采用**最小Snap轨迹**（附录B）连接 $σ_{0}​$ 和 $σ_{f}$​，闭式解为7次多项式：
    $$
	    p^{*}(t) = \sum_{i=0}^{7}a_{i}t^{i}
    $$
    - **运动代价** $J$：计算轨迹的总Snap能量 $J=\int\limits_{0}^{T}∥s(t)∥^{2}dt$，用于权衡信息增益与能耗。

#### **(2) GauSS-MI计算（Algorithm 2）**

- **输入**：候选视角 $σ$ 和当前3DGS地图 $G$。
    
- **关键步骤**：
    1. **渲染预期图像**：
        - 从 $σ$ 渲染颜色 $C^{[j]}$ 和亮度 $M^{[j]}=0.299R+0.587G+0.114B$          
        - 计算每个像素的信息增益 。
    2. **传感器先验建模**：
        - 基于相机噪声模型（Poisson-Gaussian [10]），计算 $P(z^{[j]}∣M^{[j]})$。
    3. **互信息积分**：
        $$I(σ)=\sum_{j = 1}^{n_{z}}(z^{[j]}∣M^{[j]})⋅f^{[j]}$$
- **加速策略**：
    - **多分辨率评估**：先低分辨率（1/4图像）粗选视角，再全分辨率精修。
    - **GPU并行**：每个CUDA Block处理一个候选视角。
#### **(3) 最优视角选择**
- **综合奖励**（公式23）：
    $$R=w_{I}I(σ)−w_{J}J(σ_{T})$$
    - 权重调参：$w_{I}​$ 和 $w_{J}$ 根据场景动态调整（如狭窄环境增大 $w_{J}$​ 避免碰撞）。
- **安全约束**：
    - 碰撞检测：通过3DGS地图的占据信息（如Alpha Shape）过滤不可行轨迹。
    - 视野约束：确保目标视角在传感器FOV内（如D435的87°水平FOV）。