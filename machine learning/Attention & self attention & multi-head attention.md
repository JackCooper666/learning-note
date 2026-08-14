
# Attention 
**注意力机制**其实是源自于人对于外部信息的处理能力。由于人每一时刻接受的信息都是无比的庞大且复杂，远远超过人脑的处理能力，因此人在处理信息的时候，会将注意力放在需要关注的信息上，对于其他无关的外部信息进行过滤，这种处理方式被称为注意力机制。

## Query & Key & Value

- **查询（Query）：** 指的是查询的范围，自主提示，即主观意识的特征向量
- **键（Key）：** 指的是被比对的项，非自主提示，即物体的突出特征信息向量
- **值（Value） ：**  则是代表物体本身的特征向量，通常和Key成对出现

1. 当你用上淘宝购物时，你会敲入一句关键词（比如：显瘦），这个就是**Query**。
2. 搜索系统会根据关键词这个去查找一系列相关的**Key**（商品名称、图片）。
3. 最后系统会将相应的 **Value** （具体的衣服）返回给你。


## The pipeline of the attention
1. 根据Query和Key计算两者之间的相关性或相似性（常见方法点积、余弦相似度，MLP网络），得到注意力得分.
$$
Similarity(Query, Key_{i}) = Query \cdot Key_{i}
$$
$$
Similarity(Query,Key_{i}) = \frac{Query \cdot Key_{i}}{||Query|| \cdot ||Key_{i}||}
$$
$$
Similarity(Query,Key_{i}) = MLP(Query,Key_{i})
$$
2. 对注意力得分进行缩放scale（除以维度的根号），再softmax函数.
$$
a_{i} = Softmax(Sim_{i})
$$
3. 根据权重系数对Value值进行加权求和，得到Attention Value. 

# Self-Attention
针对全连接神经网络对于多个相关的输入无法建立起相关性的这个问题，通过自注意力机制来解决，自注意力机制实际上是想让机器注意到整个输入中不同部分之间的相关性。

自注意力机制是注意力机制的变体，其减少了对外部信息的依赖，更擅长捕捉 数据或特征的内部相关性。自注意力机制的关键点在于，Q、K、V是同一个东西，或者三者来源于同一个X，三者同源。通过X找到X里面的关键点，从而更关注X的关键信息，忽略X的不重要信息。

## Pipeline 
This is the pipeline overview of the self-attention 
```
              it
               ↓
             Query
               ↓
         compare against
               ↓

The   robot   couldn't   enter   tunnel   ...
 ↓      ↓        ↓         ↓       ↓
Key    Key      Key       Key     Key

0.02   0.72     0.03      0.04    0.19
        ↑
    high attention
```
the token representation is $z = 0.72v_{robot} + 0.2v_{tunnel} + 0.1v_{other}$


The step of the Self-Attention is the similar as the Attention but using the matrix calculation
0. initalize the Q, K, and V
$$
Q = XW_{Q}
$$
$$
K = XW_{K}
$$
$$
V = XW_{V}
$$
The $W_{Q}$, $W_{K}$ and $W_{V}$ are initialized and will be trained. The X is the input such as X = Token embedding+Positional encoding​ 
1. calculate similarity by the querys and keys
$$
similarity = QK^{T}
$$
2. scale the similarity and get the attention matrix
$$
A = Softmax(\frac{QK^{t}}{\sqrt{d_{k}}})
$$
3. get the attention of each key and get the representation of each token
$$
z = AV
$$

# Multi-Head Attention

For head i:
$$
Q_{i} = QW_{i}^{Q}
$$
$$
K_{i} = KW_{i}^{K}
$$
$$
V_{i} = VW_{i}^{V}
$$

Then:

$$headi_{i}=Attention(Q_{i},K_{i}​,V_{i}​).$$

With eight heads:
$$head_{1}​,…,head_{8}.$$
Then concatenate them:
$$Concat(head_{1}​,…,head_{8}​).$$
Finally apply another linear layer:
$$MultiHead(Q,K,V) = Concat(head_{1}, \dots, head_{h})W^{O}$$




