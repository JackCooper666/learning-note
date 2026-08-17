先把所有正常图片的 patch-level features 存起来。测试时，如果某个 patch 的 feature 和所有正常 patch 都很不一样，那么它就是异常。

# prerequist:
ImageNet 可以理解成一个**超大规模的带标签自然图像数据集**，

# pipeline:
```
Image
 ↓
many patches
 ↓
feature of each patch
 ↓
compare every patch with normal memory bank
```