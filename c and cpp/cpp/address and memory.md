# &
## 1. reference
```cpp
int a = 10;
int &ref = a;  // ref is a reference to a
```
Now both `a` and `ref` refer to the **same memory**. Changing one changes the other.
## 2.  Address-of Operator
```cpp
int a = 10;
int *p = &a;   // p stores the address of a
```
# \[ \]

## 1. **数组声明与访问**
```cpp
int arr[5];          // 声明包含5个整数的数组
arr[2] = 10;         // 访问/修改第3个元素（索引从0开始）
```
- **特点**：
    
    - 固定大小（编译时确定）。
        
    - 数组名可隐式转换为指针（`arr` 等价于 `&arr[0]`）。
## 2. **动态内存分配（C风格）**
```cpp
int* p = new int[10]; // 动态分配10个整数的内存
delete[] p;           // 释放数组内存（必须用 delete[]）
```
**注意**：`new[]`/`delete[]` 需配对使用，否则可能导致内存泄漏。
## 3. **标准库容器（如 `std::vector`, `std::array`）的运算符重载**
```cpp
std::vector<int> vec = {1, 2, 3};
vec[1] = 5;          // 通过重载的 operator[] 访问元素
```
- **特点**：
    
    - 提供边界检查的 `at()` 方法（越界时抛出异常）。
        
    - `operator[]` 通常不检查边界（性能更高）。
## 4. **Lambda 表达式捕获列表**
```cpp
int x = 10, y = 20;
auto lambda = [x, &y]() { 
    return x + y;     // x 值捕获，y 引用捕获
};
```
- **捕获方式**：
    
    - `[=]`：以值捕获所有外部变量。
        
    - `[&]`：以引用捕获所有外部变量。
        
    - `[var]` 或 `[&var]`：显式指定捕获方式。

## 5. **属性说明符（C++11 起）**
```cpp
[[nodiscard]] int func(); // 提示返回值不应被忽略
[[deprecated("Use new_func()")]] void old_func();
```
**用途**：为编译器提供额外语义信息。

## 6. **多维数组**
```cpp
int matrix[3][4];     // 3行4列的二维数组
matrix[1][2] = 42;    // 访问第2行第3列
```
## 7. **用户自定义运算符重载**
```cpp
class MyContainer {
public:
    int& operator[](size_t index) { 
        return data[index]; 
    }
private:
    int data[10];
};
```
**应用场景**：为自定义类提供数组式访问接口。
## 8. **C++20 中的范围初始化（Range Initialization）**
```cpp
int arr[] {1, 2, 3};  // 初始化列表（C++11 起支持）
```

# 为指针取别名
I want to cite a pointer into the function, then I can change the address where the pointer pointing to in the function directly without a return.
The issue in your code is with the way you're trying to pass the `ans` pointer by reference. In C++, the correct syntax for passing a pointer by reference is `ListNode* &ans`, not `ListNode& *ans`.
```cpp
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode *ans = nullptr;
        traversal(headA, headB, ans);
        return ans;
    }
    
    void traversal(ListNode *headA, ListNode *headB, ListNode* &ans) {
        if (headA == nullptr || headB == nullptr) {
            return;
        }
        if (headA == headB) {
            ans = headA;
            return;
        }
        traversal(headA->next, headB->next, ans);
    }
};
```

# pointer
## pointer as function input

the address where the pointer pointing to is put into the function, if the value in the address is modified in the function, the value will be modified outside the function as well.