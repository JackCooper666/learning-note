先把所有正常图片的 patch-level features 存起来。测试时，如果某个 patch 的 feature 和所有正常 patch 都很不一样，那么它就是异常。

假设我们有一张正常螺丝图片：
$$
x
$$
通过一个 pretrained neural network：
$$
ϕ(x)
$$
得到 feature。

例如某个 patch：
$$
m=[0.2,0.7,−0.1,…]
$$
再来一个正常 patch：
$$
m2​=[0.21,0.69,−0.09,…]
$$
它们应该在 feature space 中距离比较近。

如果测试的时候来了一个 cracked patch：
$$
m_{test}​
$$
可能：
$$
∥m_{test}​−m_{normal}​∥_{2}​
$$
比较大。

所以最基础的 anomaly score 可以写成：

Anomaly Score=distance to nearest normal feature​

这就是 PatchCore 的根。

# prerequist:
ImageNet 可以理解成一个**超大规模的带标签自然图像数据集**，

# training pipeline:
```
Normal Images
↓
Frozen pretrained CNN
↓
Extract patch features
↓
Local aggregation
↓
Memory Bank
↓
Coreset sampling
↓
Done
```

## extract patch feature
the first step is get the patch features from the normal images via the pretrained CNN module. 

one patch matches one receptive field of the image
```
Original Image

+-----------------------------+
|                             |
|       +---------+           |
|       |         |           |
|       |   RF    |           |
|       |         |           |
|       +---------+           |
|                             |
+-----------------------------+
```

what is receptive field ? CNN feature map 上的一个位置 (h,w) 对应原始图片上的一片区域，这片区域叫这个 feature 的 receptive field。

## local aggregation
then the feature of the a patch is the aggregation result between it and its 8 neighbours

For a center position (h,w), the CNN first gives one feature vector:
$$
ϕ(h,w)
$$
Then PatchCore considers the 3×3 neighborhood around it:
```
A  B  C

D  X  E

F  G  H

```

where X is the center patch.

So the neighborhood contains: X+8 neighboring patch features​

and PatchCore aggregates them:
$$
ϕ(N_{3}^{(h,w)}​)=f_{agg}​({ϕ(a,b)∣(a,b)∈N_{3}^{(h,w)}​})
$$

## Memory bank
All the local aggregated patch feature will be stored in the memory bank.

## Coreset sampling
choose a subset $M_{C}$​ so that even the **worst-covered** original memory-bank point is as close as possible to some selected coreset point.


# test pipeline
```
Test Image
    ↓
Frozen Pretrained CNN
    ↓
Patch Features
    ↓
Local Aggregation
    ↓
For every patch:
Nearest Neighbor Search
    ↓
Distance to Memory Bank
    ↓
Patch Anomaly Scores
    ↓
+------------------------+
|                        |
v                        v
Max Score          Spatial Scores
|                        |
Image Anomaly      Anomaly Map
```


Firstly the test image come in, then the patch feature will be got and do the local aggregation with its neighbors.

Secondly, the nearest neighbour of each local aggregated patch in the memory bank will be found by calculate the distance between the patch's feature and the features of the patch in the memory bank.

then we can get the Patch anomaly scores
$$
m^*
=
\arg\min_{m \in \mathcal{M}}
\left\|
m_{\text{test}} - m
\right\|_2
$$
$$
d(m_{\text{test}})
=
\left\|
m_{\text{test}} - m^*
\right\|_2
$$

Then, get the image level anomaly score
PatchCore 的核心思想就是：
One anomalous patch⇒Image can be anomalous​
所以最基础 image score：
$$
s^*
=
\max_{m_{\text{test}} \in P(x_{\text{test}})}
\min_{m \in \mathcal{M}}
\left\|
m_{\text{test}} - m
\right\|_2
$$

finally, re-weight the image score according to the nearest neighbours on the input image of hte patch to get the final $s$


# 那 anomaly segmentation 怎么得到？

这个其实特别自然。

因为每一个 test patch 都有：
$$
d_{i}​
$$
例如：
```
0.1   0.2   0.1   0.2

0.1   0.2   4.5   3.8

0.2   0.3   4.1   3.5

0.1   0.2   0.3   0.2
```

那么：
```
4.5

4.1

3.8

3.5
```

这一片就是 anomaly region。

所以把：

patch anomaly scores

放回原来的 spatial positions：
$$
(h,w)
$$
就得到 low-resolution anomaly map。

然后：

bilinear interpolation

放大到原始 image size。

论文最后还用了： Gaussian smoothing $σ=4​$


所以：

PatchCore detection​

和：

PatchCore segmentation​

其实使用的是同一套 patch anomaly scores。

区别只是：
$$
image-level=max(patch scores)
$$
而：
segmentation=spatial arrangement of patch scores