The main idea:
Instead of reading a sentence sequentially like an RNN, let every token directly look at every other token and decide which ones are important.

```
Input sentence
      ↓
 Input Embedding
      +
Positional Encoding
      ↓
┌──────────────────┐
│     Encoder      │ × 6
│                  │
│ Multi-Head Attn  │
│       ↓          │
│ Feed Forward     │
└──────────────────┘
      ↓
Encoder output
      ↓
      ↓ used by decoder
      ↓
┌──────────────────┐
│     Decoder      │ × 6
│                  │
│ Masked Attention │
│       ↓          │
│ Cross Attention  │
│       ↓          │
│ Feed Forward     │
└──────────────────┘
      ↓
    Linear
      ↓
    Softmax
      ↓
Next token probability
```

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

so for one token the PE of it will be 
PE(pos) = [PE(pos,0), PE(pos, 1), ..., PE(2,511)]





