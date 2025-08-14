# normal Lambda
Lambda 函数是 C++11 引入的一种匿名函数特性，它允许你在需要函数的地方快速定义一个函数对象，而无需单独命名和定义。

## 基本语法
```cpp
[capture](parameters) -> return_type { 
    // 函数体
}
```
## 组成部分

1. **捕获列表 (capture clause)** - `[]`
    - 定义哪些外部变量可以在 lambda 体内使用
    - 示例：
        - `[]` 不捕获任何变量
        - `[x, &y]` 按值捕获x，按引用捕获y
        - `[=]` 按值捕获所有外部变量
        - `[&]` 按引用捕获所有外部变量
        - `[this]` 捕获当前类的this指针
            
2. **参数列表 (parameters)** - `()`
    - 与普通函数的参数列表类似
    - 可以省略（如果没有参数）
        
3. **可变规范 (mutable)** - 可选
    - 允许修改按值捕获的变量
    - 示例：`[x](int a) mutable { x++; }`
        
4. **异常规范 (exception specification)** - 可选
    - 例如：`noexcept`
        
5. **返回类型 (return type)** - `-> type` 可选
    - 如果省略，编译器会自动推导返回类型
    - 当函数体中有多个return且类型不同时需要显式指定
        
6. **函数体** - `{}`
    - 包含lambda的实际代码

## 使用示例

### 基本示例
```cpp
auto sum = [](int a, int b) { return a + b; };
std::cout << sum(5, 3);  // 输出8
```


### 带捕获的示例
```cpp
int x = 10;
auto add_x = [x](int a) { return a + x; };
std::cout << add_x(5);  // 输出15
```
### 修改捕获的变量
```cpp
int x = 1;
auto increment = [x]() mutable { return ++x; };
std::cout << increment();  // 输出2
std::cout << x;  // 输出1（x是按值捕获的副本）
```

### 返回类型指定
```cpp
auto divide = [](int a, int b) -> double {
    if(b == 0) return 0.0;
    return static_cast<double>(a)/b;
};
```
## Lambda的类型
每个lambda表达式都有唯一的、未命名的类型。如果需要存储lambda，可以使用：
- `auto` 关键字
- `std::function`（需要包含`<functional>`头文件）
```cpp
#include <functional>
std::function<int(int)> square = [](int x) { return x * x; };
```

## 应用场景

1. **STL算法**：
```
std::vector<int> v = {1, 2, 3, 4};
std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });
```
    
2. **回调函数**：
```cpp
button.onClick([](){ std::cout << "Button clicked!"; });
```    
2. **多线程**：
```cpp
std::thread t([](){ std::cout << "Hello from thread"; });
    t.join();
```
    
3. **延迟执行**：
```cpp
auto later = [](){ /* 稍后执行的代码 */ };
// ...
later();
```

## C++14和C++17的增强

- **C++14**：
    - 泛型lambda：参数可以使用`auto`
```cpp
auto print = [](const auto& x) { std::cout << x; };
```
    
- 捕获表达式：
```cpp
auto ptr = std::make_unique<int>(10);
auto lambda = [p = std::move(ptr)](){ /* 使用p */ };
```        
- **C++17**：
    - `constexpr` lambda：
```cpp
constexpr auto square = [](int x) { return x * x; };
static_assert(square(5) == 25);
```        

Lambda函数大大简化了C++中的函数对象创建，使代码更加简洁和灵活。

# recursion Lambda
Lambda 表达式在 C++ 中实现递归有一些特殊的技巧和注意事项，因为 lambda 本质上是匿名函数，无法直接通过名称调用自身。
## 实现递归 Lambda 的几种方法
### 1. 使用 std::function (C++11)
```cpp
#include <functional>

std::function<int(int)> factorial = [&](int n) {
    return n <= 1 ? 1 : n * factorial(n-1);
};
```
### 2. 使用 Y 组合子 (高级技巧)
```cpp
auto y_comb = [](auto f) {
    return [f](auto... args) {
        return f(f, args...);
    };
};

auto factorial = y_comb([](auto self, int n) -> int {
    return n <= 1 ? 1 : n * self(self, n-1);
});
```
### 3. 使用 C++23 的显式 this 捕获
```cpp
auto factorial = [](this auto self, int n) {
    return n <= 1 ? 1 : n * self(n-1);
};
```
### 4. 通过参数传递自身引用
```cpp
auto factorial = [](auto& self, int n) -> int {
    return n <= 1 ? 1 : n * self(self, n-1);
};

// 调用方式
int result = factorial(factorial, 5);
```