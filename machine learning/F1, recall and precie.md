先定义四个最基本的量：
- **TP (True Positive)**：真实是正类，预测也是正类
- **FP (False Positive)**：真实是负类，但预测成正类
- **FN (False Negative)**：真实是正类，但预测成负类
- **TN (True Negative)**：真实是负类，预测也是负类

# Precision
$$
Precision = \frac{TP}{TP+FP}
$$
所以 Precision 关注的是：预测出来的正类准不准
# Recall
它回答的问题是： **所有真实正类中，模型找出来了多少？**
$$
Recall = \frac{TP}{TP + FN}
$$

# F1-score
是 Precision 和 Recall 的 **harmonic mean（调和平均）**。
$$
F1 = 2\frac{Precision \cdot Recall}{Precision + Recall}
$$


# Accuracy
所有样本里，我总共预测对了多少？
$$
Accuracy = \frac{TP + TN}{TP + TN + FP + FN}
$$
