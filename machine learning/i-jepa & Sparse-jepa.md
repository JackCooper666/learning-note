# i-jepa
I-JEPA 的核心目的是训练一个好的视觉表征模型。它在自监督预训练过程中，人为遮挡图像的一部分，让模型利用可见区域的信息去预测被遮挡区域的高层 representation，而不是预测具体像素。通过不断完成这种预测任务，Encoder 学会图像中的语义和空间关系。训练完成后，我们主要使用这个 pretrained Encoder 提取图像特征，再提供给分类、深度估计等下游任务。

## Pretraining Prediction Pipeline
1. Input an image and sample context and target block masks.
	- The context encoder does not see the target regions.
	- It only receives the visible context patches.
2. The context encoder generates representations of the visible context patches. $$s_{x} = f_{\theta}(x)$$ It does not generate a representation of the complete image, because the target patches have been removed.
3. The predictor predicts the representations of the patches inside each target block, using:
	- the context representation $s_{x}$, and
	- mask tokens containing the positions of the target patches $$\hat{s}_y(i) = g_\phi\left(s_x, \{m_j\}_{j \in B_i}\right)$$
%% 
1. image input with target block masks
2. context encoder generates the representation of the image
3. Predictor predicts the representation of patches in the target blocks accroding to the representations from the context encorder
%%
## Training pipeline
The training pipeline mainly contents three parts:
### context encoder
input the visible patches $x$, then get the representation fo the patches $$s_{x} = f_{\theta}(x)$$the $\theta$ is the params in the context encoder needs to be trained , such as the params in the transformer of it.
### target encoder
1. the full image inputs into the target encoder which will divide the image into several patches and get the representations of those patches. $$s_{y} = f_{\bar \theta}(y)$$. The $\bar \theta$ is the params in the traget encoder needs to be trained.
2. choose the several target blocks, each contains several patches. and get the position enbedding of each target blocks

### predictor 
1. predict the representations of target blocks according the representations from the context encoder and the position embedding. $$\hat s_{y}(i) = g_{\phi}(s_{x},m_{i})$$ where $\phi$ is the params needs to be updated, $s_{x}$ is the representations of the context encoder, $m_{i}$ is mask token + positional embedding.
### loss calculation
The loss is 