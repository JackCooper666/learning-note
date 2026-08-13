```
                    Neural Network Training
                             │
              ┌──────────────┴──────────────┐
              │                             │
         From Scratch                Use Pretrained Model
              │                             │
        Random weights               Pre-trained weights
                                            │
                                   Transfer Learning
                                            │
                         ┌──────────────────┴───────────────┐
                         │                                  │
                  Frozen Backbone                    Fine-tuning
                         │                                  │
                  train Head only             ┌─────────────┴──────────┐
                                              │                        │
                                       Partial Fine-tune       Full Fine-tune
```

# From Scratch:

一个神经网络刚建立的时候，随机初始化里面的参数.

# Pre-training
先让模型在一个较大的数据集上学到通用能力。

# Fine-tuning
在已经学好的模型基础上，用你的任务数据继续训练。

# Frozen Backbone：冻结 Backbone

假设你有一个 pretrained DINO：
```
DINO Backbone
     +
Classifier
```

Backbone 不训练。只有 classifier 更新

```
DINO Backbone
     🔒
    Frozen
       ↓
   Features
       ↓
Classifier
     🔓
    Train
```


# Fine-tuning 还可以分程度

Fine-tuning 不是非黑即白的。

实际上有三种很常见方式。

### ① Linear probing

```
Backbone 🔒
Head     🔓
```

只训练 head。

---

### ② Partial Fine-tuning

```
Early Backbone   🔒
Middle Backbone  🔒
Last Layers      🔓
Head             🔓
```

只训练最后几层。

---

### ③ Full Fine-tuning

```
Entire Backbone 🔓
Head            🔓
```

全部训练。
