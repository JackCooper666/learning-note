In C++, the `std::sort()` function is a highly flexible algorithm that can sort various types of data structures. Below is a breakdown of what can be passed to `std::sort()`:

# **1. Supported Containers (Templates)**

`std::sort()` works on **random-access iterators**, meaning it can sort:

- **Arrays** (C-style or `std::array`)
    
- **Vectors** (`std::vector`)
    
- **Deques** (`std::deque`)
    
- **Strings** (`std::string`)

```cpp
#include <algorithm>
#include <vector>
#include <array>
#include <string>

int main() {
    // Sorting a C-style array
    int arr[] = {5, 2, 9, 1};
    std::sort(arr, arr + 4); // Sorts to {1, 2, 5, 9}

    // Sorting a std::vector
    std::vector<int> vec = {5, 2, 9, 1};
    std::sort(vec.begin(), vec.end()); // Sorts to {1, 2, 5, 9}

    // Sorting a std::string
    std::string str = "hello";
    std::sort(str.begin(), str.end()); // Sorts to "ehllo"

    return 0;
}
```

---

# **2. Variable Types That Can Be Sorted**

`std::sort()` can sort elements of **any type** that supports **comparison operations** (`<`, `>`, or custom comparators). This includes:

- **Primitive types** (`int`, `float`, `char`, etc.)
    
- **Custom objects** (if `operator<` is defined or a comparator is provided)
    
- **Pairs and tuples** (sorted lexicographically)
    

## **Example: Sorting Custom Objects**
```cpp
#include <algorithm>
#include <vector>

struct Person {
    std::string name;
    int age;
    bool operator<(const Person& other) const {
        return age < other.age; // Sort by age
    }
};

int main() {
    std::vector<Person> people = {{"Alice", 30}, {"Bob", 25}, {"Charlie", 35}};
    std::sort(people.begin(), people.end()); // Sorts by age

    return 0;
}
```

# **3. Custom Comparators (for Advanced Sorting)**

If you need a **different sorting order**, you can pass a **comparator function** (`lambda`, `std::greater`, or a custom function).

## **Example: Sorting in Descending Order**

```cpp
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> nums = {5, 2, 9, 1};

    // Using std::greater for descending order
    std::sort(nums.begin(), nums.end(), std::greater<int>()); // Sorts to {9, 5, 2, 1}

    // Using a lambda for custom sorting (e.g., even numbers first)
    std::sort(nums.begin(), nums.end(), [](int a, int b) {
        return (a % 2 == 0) && (b % 2 != 0);
    });

    return 0;
}
```