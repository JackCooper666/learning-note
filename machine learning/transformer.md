The main idea:
Instead of reading a sentence sequentially like an RNN, let every token directly look at every other token and decide which ones are important.

# The entire original Transformer

We can now reconstruct Figure 1.

## Encoder

Input:

x1​,…,xN​

then:

Embedding + Positional Encoding

then six times:

Multi-Head Self-Attention​ 
↓ 
Add + LayerNorm​ 
↓ 
Feed Forward​ 
↓ 
Add + LayerNorm​

---

## Decoder

Output tokens shifted right:

y0​,y1​,…,yM−1​

then:

Embedding+PositionalEncoding

then six times:

Masked MultiHead SelfAttention​ 
↓ 
EncoderDecoder Attention​ 
↓ 
FeedForward​

and finally:

Linear​ 
↓ 
Softmax​ 
↓ 
P(next token).

# Embedding: turning a token into a vector

1. each token hasa unique token ID
2. set the vocabulary library size $V$ and demention $d_{model}$ of the embedding table $E$ manually
$$
E \in \mathbb{R}^{V \times d_{model}}
$$
3. convert each token by row in the embedding table whose row index matching the token ID.
4. the params in the embedding table will be iterated and optimized during the training of the transformer.
# positional encoding
The transformer needs to know the position of the token in the sentence

so actual transformer input is 
	Actual Transformer input=Token embedding+Positional encoding​
For example:
```
             Embedding        Position
"I"        [....512....]    + [....512....]
"love"     [....512....]    + [....512....]
"machine"  [....512....]    + [....512....]
```

The positional encoding (PE) of a token is represented by the sin and cos functions.
$$
PE_{(pos,2i)} = sin(\frac{pos}{10000^{\frac{2i}{d_{model}}}})
$$
$$
PE_{(pos,2i+1)} = cos(\frac{pos}{10000^{\frac{2i}{d_{model}}}})
$$
where $pos$ is the position of the token in the sentence, $2i$ and $2i + 1$ indicate the even and odd. 
so for one token the PE of it will be 
$$
PE(pos) = [PE(pos,0), PE(pos, 1), ..., PE(2,511)]
$$

# Multi head Attention 
see the Attention & self-Attention & multi-head attention section

# Feed-forward network (FFN)
Both the weights and the biases in the FFN are trainable parameters and are updated during training.

In the Transformer, the **FFN is basically an MLP**.

# Mask attention

The decoder first looks at its own previous tokens.

For example when predicting:
```
学习
```

it can see:
```
我 喜欢 机器
```

But there's a major problem during training.

We already know the complete correct sentence:
```
我 喜欢 机器 学习
```

If the model could see `"学习"` while trying to predict `"学习"`, that's cheating.

So we need a mask to mask the attention matrix where the tokens have been used

So: Decoder token i can only see tokens ≤i​, This preserves **autoregressive generation**.

# Encoder-decoder attention / cross-attention

For decoder self-attention:
$$Q,K,V$$

all come from the decoder.

But for encoder-decoder attention:

Q=decoder representation

while

K,V=encoder outputs.

# final output

> The final Softmax outputs a probability over **the entire target-language vocabulary**, not only the Chinese tokens that have not been translated yet.

Suppose the Chinese vocabulary contains

V=32,000

tokens. 

At one decoding step, the final linear layer produces
$$
z \in \mathbb R^{32,000}$$

and Softmax converts those 32,000 scores into
$$
P(y_{t+1}|y_{1}, \dots, y_{t}, English sentence)
$$

then choose the one with highest probability

# how to train
一次前向传播中，同时对所有中文位置预测“下一个 token 的概率分布”，然后把所有位置的 loss 一起算出来。
以这个例子来说：

English: I love machine learning

正确中文是：

我 喜欢 机器 学习

训练时，Decoder 的输入不是空的，而是把正确答案整体右移一位：

$[<BOS>,我,喜欢,机器]$

而真正要预测的目标是：

$[我,喜欢,机器,学习]$

原论文明确说明，decoder 的输出 embedding 会右移一位，同时使用 mask，保证第 i 个位置只能看到它前面的输出 token。

所以一次 forward 里面，其实同时做了这些事情：

```markdown
|Decoder 当前能看到的中文|应该预测|
|---                   |---|
|`<BOS>`               |我|
|`<BOS> 我`            |喜欢|
|`<BOS> 我 喜欢`        |机器|
|`<BOS> 我 喜欢 机器`    |学习|
```


也就是说，模型会同时得到：

P1​(所有中文词) 
P2​(所有中文词) 
P3​(所有中文词) 
P4​(所有中文词)

然后分别看正确 token 的概率。

比如：

$P_{1}​(我)=0.8 P_{2}​(喜欢)=0.6 P_{3}​(机器)=0.7 P_{4}​(学习)=0.5$

那么四个位置的 loss 可以写成：

$$
L1​=−log0.8 
$$
$$
L2​=−log0.6 
$$
$$
L3​=−log0.7 
$$
$$L4​=−log0.5$$

最后：

$$L=\frac{L_{1}​+L_{2}​+L_{3}​+L_{4}}{4}​​$$​

然后才进行：

L→Backpropagation→更新 Transformer 参数

真正的 cross-entropy 是：

L=−i=1∑V​yi​logpi​​

其中：

- V：词表大小
- pi​：模型预测第 i 个 token 的概率
- yi​：**ground truth**
- y 通常是 one-hot vector

比如当前应该预测：

我​

假设词表只有：

$[我,你,他,喜欢]$

那么 ground truth 是：

$y=[1,0,0,0]$

模型的预测是：

$p=[0.8,0.1,0.05,0.05]$

代入 cross-entropy：

$L=−[1log0.8+0log0.1+0log0.05+0log0.05]$
$L = -log(0.8)$

假设词表只有： $[我,你,他,喜欢]$ 那实际中的词表是不是整个汉语词典，然后$y=[...., 1,....]$, 1 是词典里与ground truth对应的位置

但实际情况通常不是“整个汉语词典”，而是：

模型自己的 tokenizer 词表​

这个词表里会包含汉字、词、子词、标点、特殊符号等 token，而不一定是传统意义上的“汉语词典”。

比如模型词表大小是：

V=32000

那么 ground truth 可以概念上写成：

$y=[0,0,…,1,…,0]$

其中那个 1 的位置，就是**正确 target token 在词表中的 token ID**。