# cmath
```cpp
#include <cmath>
```

## pow()
$$
powered = base^{order}
$$
```cpp
int powered;
int base;
int order
powered = pow(base,order);
```

## fabs()
`fabs()` is a **function from the C standard math library** that computes the **absolute value of a floating-point number** (like `float`, `double`, or `long double`).
```cpp
fabs((LidarMeasures.last_lio_update_time - _first_lidar_time) - plot_time)
```

## max()
The `max()` function is a **standard utility** in C++ that **returns the larger of two or more values**. It is part of the `<algorithm>` header (for general use) and also available in `<cmath>` for numeric comparisons.
```cpp
#include <algorithm>  // Required header

// Returns the larger of a and b
auto result = std::max(a, b);
```
- **Parameters**:
    - `a`, `b`: Values to compare (can be integers, floats, strings, or custom objects).
- **Return Value**:
    - The **greater** of the two values.
 ### **For Multiple Values (C++11+)**
 ```cpp
 auto result = std::max({val1, val2, val3, ...});  // Initializer list
```
```cpp
cout << std::max({3, 1, 4, 1, 5});  // Output: 5
```

# random
```cpp
#include <random>
```
```cpp
int main() {
    // 创建随机数引擎
    std::random_device rd;  // 用于获取随机种子
    std::mt19937 gen(rd()); // 使用 Mersenne Twister 引擎
    
    // 定义随机数范围（例如0-99）
    std::uniform_int_distribution<> dis(0, 99);
    
    // 生成随机数
    int random_number = dis(gen);
    
    std::cout << "随机数: " << random_number << std::endl;
    
    return 0;
}
```
