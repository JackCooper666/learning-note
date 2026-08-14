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
