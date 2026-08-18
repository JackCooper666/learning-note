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


## 