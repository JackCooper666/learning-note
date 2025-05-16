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
