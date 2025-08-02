在计算中间值时，使用 `int mid = left + (right - left) / 2;` 而不是 `int mid = (left + right) / 2;`，主要是为了避免 **整数溢出（integer overflow）** 的问题，并确保计算的正确性和安全性。

---

### **1. 为什么 `(left + right) / 2` 可能有问题？**

当 `left` 和 `right` 都是很大的正整数时，`left + right` 可能会超出 `int` 类型的最大值（例如，`INT_MAX = 2³¹ - 1 = 2,147,483,647`），导致 **溢出（overflow）**，计算结果会变成负数或错误的值。

```cpp
int left = 2'000'000'000;  // 20亿
int right = 2'000'000'000; // 20亿
int mid = (left + right) / 2; // 40亿 > INT_MAX → 溢出！
```

`left + right = 4,000,000,000`，但 `INT_MAX = 2,147,483,647`，所以 `left + right` 会溢出成一个负数（如 `-294,967,296`），导致 `mid` 计算错误。

### **2. 为什么 `left + (right - left) / 2` 更安全？**

`right - left` 不会溢出，因为 `right >= left`（在二分查找或 BST 构建中，`right` 不会小于 `left`），所以 `(right - left) / 2` 是一个安全的计算方式。

```cpp
int left = 2'000'000'000;
int right = 2'000'000'000;
int mid = left + (right - left) / 2; // right - left = 0 → mid = left = 2'000'000'000
```


