current issue
![[adefaa453af4299b0f16e8835fb37f90.jpg]]

在RS-FASTLIVO这一功能的实现部分，所有降采样的点云的法线方向光心射线方向的夹角会被计算，然后夹角超过阈值的点的权重会通过 `pt_copy.intensity = weight;` 来赋予。

那么，需要保留的点和噪点会有不同的权重

然后，请问，这里使用过权重之间的区别对点进行过滤吗？

如果是这样的话，这一部分的代码在哪？是这个ProjCloudToImageToGetFeature 里吗？

因为这个ProjCloudToImageToGetFeature对将采样的点云做了投影以方便投影点的reference path对应的图块和现图块之间的匹配，所以这个滤除应该在这个函数的开始部分，可我没找到



没有直接过滤点。存到了点的weight_字段，在优化时用来给光度误差降权。
Jimg = Jimg * (1.0/scale) * pt->weight_ * pt->weight_2_ * pt->weight_3_ * pt->weight_4_;
