# auto
In C++, the `auto` keyword is used for **automatic type deduction** — it tells the compiler to infer the variable's type from its initializer.

## ✅ Benefits
1. **Reduces verbosity**:
```cpp
std::vector<int>::iterator it = v.begin();
auto it = v.begin(); // Cleaner
```