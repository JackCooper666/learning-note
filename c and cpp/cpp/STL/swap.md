In C++, **`std::swap(a, b)`** requires `a` and `b` to be of the **same type**, but this type can be **any valid C++ type**, including:

- Fundamental types (`int`, `float`, `char`, etc.)
    
- Standard Library containers (`std::vector`, `std::string`, `std::deque`, etc.)
    
- User-defined types (if they support copy/move operations)

```cpp
int x = 5, y = 10;
std::swap(x, y);  // OK
```

