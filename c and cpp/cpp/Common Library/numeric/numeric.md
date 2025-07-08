```cpp
#include <numeric>
```

# gcd() and lcm()

```cpp
#include <iostream>
#include <numeric>  // 包含 gcd() 和 lcm()
using namespace std;

int main() {
    int a = 12, b = 18;

    cout << "GCD: " << gcd(a, b) << endl; // 输出 6
    cout << "LCM: " << lcm(a, b) << endl; // 输出 36

    return 0;
}

```
- 需要 **C++17** 或更高版本编译器支持。
- `gcd()` 和 `lcm()` 只支持整型参数（如 `int`, `long`, `long long` 等）。
- 编译时记得加上 C++17 标志，例如：
```bash
g++ main.cpp -std=c++17
```

## ✅ **GCD (Greatest Common Divisor)**

The **GCD** of two integers is the **largest number** that **divides both numbers exactly** (no remainder).
### Example:
- GCD of 12 and 18 is **6**, because:
    - 12 = 6 × 2   
    - 18 = 6 × 3
    - And 6 is the biggest number that divides both.

---

## ✅ **LCM (Least Common Multiple)**

The **LCM** of two integers is the **smallest number** that is a **multiple of both numbers**.
### Example:
- LCM of 12 and 18 is **36**, because:
    - 36 is the smallest number that both 12 and 18 divide into:
        - 36 ÷ 12 = 3
        - 36 ÷ 18 = 2

---

## 🔁 Relationship between GCD and LCM:

For any two positive integers `a` and `b`:

$\text{GCD}(a, b) \times \text{LCM}(a, b) = a \times b$

### Example again:

- 12 × 18 = 216
- GCD = 6, LCM = 36
- 6 × 36 = 216 ✅