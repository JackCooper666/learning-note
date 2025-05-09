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