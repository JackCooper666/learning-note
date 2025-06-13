`emplace_back()` 是 C++11 引入的 STL 容器（如 `std::vector`, `std::deque`, `std::list` 等）的成员函数，用于在容器末尾直接构造新元素，比 `push_back()` 更高效。
```cpp
#include <vector>
#include <string>

int main() {
    std::vector<std::string> vec;
    
    // 使用 push_back (需要构造临时对象)
    vec.push_back(std::string("Hello"));  // 创建临时string对象，然后移动
    
    // 使用 emplace_back (直接在vector内存中构造)
    vec.emplace_back("World");  // 直接用参数构造string
    
    return 0;
}
```