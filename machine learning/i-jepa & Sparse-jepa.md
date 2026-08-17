# i-jepa
I-JEPA 的核心目的是训练一个好的视觉表征模型。它在自监督预训练过程中，人为遮挡图像的一部分，让模型利用可见区域的信息去预测被遮挡区域的高层 representation，而不是预测具体像素。通过不断完成这种预测任务，Encoder 学会图像中的语义和空间关系。训练完成后，我们主要使用这个 pretrained Encoder 提取图像特征，再提供给分类、深度估计等下游任务。

## Normal Output Pipeline
1. image input with target block masks
2. context encoder generates the representation of the image
3. Predictor predicts the representation of patches in the target blocks accroding to the representations from the context encorder
## Training