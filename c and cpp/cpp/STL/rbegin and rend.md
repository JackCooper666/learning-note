# **1. Containers Supporting `rbegin()` and `rend()`**

These functions are defined for **all standard containers that support bidirectional or random-access iteration**, including:

## **Sequential Containers**

| Container     | Example Usage (`rbegin()` → `rend()`)                  |
| ------------- | ------------------------------------------------------ |
| `std::string` | `for (auto it = s.rbegin(); it != s.rend(); ++it)`     |
| `std::vector` | `reverse(vec.begin(), vec.end())`                      |
| `std::deque`  | `sort(dq.rbegin(), dq.rend())`                         |
| `std::list`   | `lst.reverse()` (or use `rbegin()`)                    |
| `std::array`  | `for (auto it = arr.rbegin(); it != arr.rend(); ++it)` |

## **Associative Containers (C++14+)**

| Container       | Notes                                |
| --------------- | ------------------------------------ |
| `std::set`      | Iterates in **reverse sorted order** |
| `std::map`      | Iterates key-value pairs in reverse  |
| `std::multiset` | Same as `set`, allows duplicates     |
| `std::multimap` | Same as `map`, allows duplicate keys |

## **Container Adaptors (Limited Support)**

| Container             | Notes                                          |
| --------------------- | ---------------------------------------------- |
| `std::stack`          | No direct iterators (use underlying container) |
| `std::queue`          | No direct iterators                            |
| `std::priority_queue` | No direct iterators (always sorted)            |
