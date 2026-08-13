**token 可以理解成“送进 Transformer 的一个基本信息单元”**。

关键是：**token 不一定是一个单词。**

对于文本，比如：

```
I love robotics
```

经过 tokenizer 以后，可能变成：

```
["I", "love", "robot", "ics"]
```

这里每一个：

```
"I"
"love"
"robot"
"ics"
```

就是一个 token。

然后每个 token 会被转换成一个向量：

$$
x_i \in \mathbb{R}^{d}
$$

例如一句话有 N 个 token，那么输入 Transformer 的就是：

$$
X =
\begin{bmatrix}
x_1 \\
x_2 \\
\vdots \\
x_N
\end{bmatrix}
\in \mathbb{R}^{N \times d}
$$

这里：

- N：token 数量
- d：每个 token 的特征维度