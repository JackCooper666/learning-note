一个 sonar 最简单的工作过程是：
```
Sonar
  |
  |  发出声波 ping
  v
       object
          |
          | reflection
          v
Sonar <----
```
What sonar will measure
1. TIme of Flight to measure the distance
2. Intensity sonar 会测： 回来的声音有多强。
于是你可以把一个 sonar measurement 简化理解成：
$$
(r,I)
$$
也就是：
```
这个方向上
3.2 m 的地方
收到一个 intensity = 0.8 的 echo
```

# imaging sonar
它最终生成一个二维矩阵：
$$
I(r,ϕ)
$$
其中：

- $r$：range
- $ϕ$：azimuth
- $I$：echo intensity

每一个 pixel 其实表示：
> 在某个 **range + azimuth** 区间里接收到多少声波能量。