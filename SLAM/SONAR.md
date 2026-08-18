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


这里有一个非常重要的东西：
$$
Elevation 信息丢失​
$$
也就是说：

真实世界：
$$
(r, φ, θ)
$$
  

sonar image：
$$
(r, φ)
$$
其中：
$$
θ=elevation
$$
被压缩掉了。


# side-scan sonar
Side-scan sonar：左右各打一个宽扇形声束，但不会像 multibeam sonar 那样把这个扇形再分成很多可区分角度的 beam。它主要保留 range + intensity，而丢掉 beam 内部的 azimuth 信息。

比如右侧这一整个扇形：
```
          object A

                ●

             /

           /

Sonar ● ---------------- ● object B

           \

             \

                ● object C
```

A、B、C 都在这个 fan beam 里面。

假设它们距离 sonar 都是：
$$
r=5m
$$
那么 side-scan sonar 很难告诉你：
```
A 在 20°

B 在 40°

C 在 60°
```

它主要知道： 5m 这个 range 上收到了多少 intensity​

所以一侧的一次 ping 最终更像生成：
$$
I(r)
$$
也就是：
```
range

0m   1m   2m   3m   4m   5m   6m

 |    |    |    |    |    |    |

░░   ░░   ░░   ░░   ░░   ██   ░░

                         ↑

                 strong return
```

# Multibeam Profiling Sonar

```
           vehicle
              ↓

   \ | | | | | | | /
    \| | | | | | |/
~~~~~~~~~~~~~~~~~~~~ seabed
```

zimuth 很宽，但：
$$
Elevation
$$
非常窄，论文给出的典型值大约：
$$
1^{∘}∼3^{∘}
$$
因此每一帧基本可以当成：2D slice​

论文描述它可以得到下方环境的一排 measurements。

# Echosounder

单束测深

```
          sonar
           \ | /
            \|/
             V
          cone beam
             |
             |
~~~~~~~~~~~~ seabed
```
它通常不告诉你：

azimuth

也不告诉你：

elevation

主要就是：

range+intensity


# 3D sonar

可以把 3D sonar 想成“二维 beam grid”

普通 multibeam profiling sonar 类似：
$$
1×N
$$
beam array：
```
beam:
1  2  3  4  5  6  7  8

|  |  |  |  |  |  |  |
```

---

3D sonar 更接近：
$$
M×N
$$
例如概念上：
```
             azimuth →

  

        beam beam beam beam

          ↓    ↓    ↓    ↓

  

elevation  ●    ●    ●    ●

   ↓       ●    ●    ●    ●

           ●    ●    ●    ●

           ●    ●    ●    ●

```
每一个 angular cell 都对应：
$$
(ϕ_{i}​,θ_{j}​)
$$
再测一个 range：
$$
r_{ij}​
$$
于是：
$$
(r,ϕ,θ)​
$$
全都有了。