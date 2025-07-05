
# **1. For Floating-Point Types (`float`, `double`, `long double`)**

Use `std::numeric_limits` from the `<limits>` header:
## **Infinitely Large (Positive Infinity)**
```cpp
#include <iostream>
#include <limits>

int main() {
    double pos_inf = std::numeric_limits<double>::infinity();
    float pos_inf_f = std::numeric_limits<float>::infinity();
    
    std::cout << "Positive infinity (double): " << pos_inf << "\n";
    std::cout << "Positive infinity (float): " << pos_inf_f << std::endl;
    return 0;
}
```

### **Output:**
```text
Positive infinity (double): inf  
Positive infinity (float): inf
```

## **Infinitely Small (Negative Infinity)**
```cpp
double neg_inf = -std::numeric_limits<double>::infinity();
std::cout << "Negative infinity: " << neg_inf; // Output: -inf
```

### **Checking for Infinity**
```cpp
double x = pos_inf;
if (x == std::numeric_limits<double>::infinity()) {
    std::cout << "x is +inf\n";
}
if (std::isinf(x)) { // Alternative from <cmath>
    std::cout << "x is infinite\n";
}
```

# **2. For Integer Types (`int`, `long`, etc.)**

Integers **cannot represent true infinity**, but you can use:
- **The largest/smallest possible value** as a substitute.
- **Special sentinel values** (e.g., `INT_MIN`/`INT_MAX`).
## **Infinitely Large (Maximum Value)**
```cpp
#include <climits> // For INT_MAX, INT_MIN

int pseudo_pos_inf = INT_MAX; // Largest possible integer
std::cout << "Pseudo +inf (int): " << pseudo_pos_inf; // e.g., 2147483647
```

## **Infinitely Small (Minimum Value)**
```cpp
int pseudo_neg_inf = INT_MIN; // Smallest possible integer
std::cout << "Pseudo -inf (int): " << pseudo_neg_inf; // e.g., -2147483648
```

## **Using `std::numeric_limits` (Modern C++)**
```cpp
#include <limits>

int max_int = std::numeric_limits<int>::max();
int min_int = std::numeric_limits<int>::lowest(); // or min() for floating-point
```