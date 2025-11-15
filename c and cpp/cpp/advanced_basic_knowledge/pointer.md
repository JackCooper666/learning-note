# shared_ptr
`std::shared_ptr<T>` 是 C++11 引入的 **智能指针**，用来**自动管理内存**。
它是一个“**共享所有权（shared ownership）**”的智能指针：
- 多个 `shared_ptr` 可以指向同一个对象；
- 内部有一个 **引用计数（reference count）**；
- 当最后一个 `shared_ptr` 被销毁时，指向的对象会自动 `delete`；
你不需要手动 `delete`。
```cpp
std::shared_ptr<int> p1(new int(10));
std::shared_ptr<int> p2 = p1;  // p1, p2 都指向同一个 int
```

# make_shared
`std::make_shared<T>()` 是一个 **创建 shared_ptr 的更推荐、更安全的方式**。
```cpp
auto p = std::make_shared<int>(10);
```

# 