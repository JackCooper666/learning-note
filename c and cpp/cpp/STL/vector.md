```cpp
std::vector<int> table(26, 0);
```
1. **`std::vector<int>`**
    
    - A dynamic array that can store integers (`int`).
        
2. **`table(26, 0)`**
    
    - **`26`**: The size of the vector (26 elements).
        
    - **`0`**: The initial value for all 26 elements.

# anonymous vector
In C++, an “anonymous vector” typically refers to a **temporary unnamed `std::vector` object** — a `std::vector` that's created and used **on the fly**, without assigning it to a named variable.
```cpp
//Here, `{1, 2, 3}` is automatically deduced as a `std::vector<int>` and passed to `printVector`. You don’t name it — you just use it directly.
#include <iostream>
#include <vector>

void printVector(const std::vector<int>& v) {
    for (int num : v) std::cout << num << " ";
    std::cout << "\n";
}

int main() {
    // anonymous vector used as a function argument
    printVector({1, 2, 3});  // ← this is an anonymous vector
}

```
e.g.
```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        set<vector<int>> ans_set;
        int n = nums.size();

        for (int i = 0; i < n - 2; ++i) {
            int left = i + 1;
            int right = n - 1;
            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];
                if (sum == 0) {
                    ans_set.insert({nums[i], nums[left], nums[right]});
                    ++left;
                    --right;
                } else if (sum < 0) {
                    ++left;
                } else {
                    --right;
                }
            }
        }

        return vector<vector<int>>(ans_set.begin(), ans_set.end());
    }
};

```
# resize(size_t n)

## Purpose: **Changes the actual size** of the container.

**!!!!!!!!  but after resize the size of the container will be fixed and cannot be changed**


## Meaning:

- Sets the container to have **exactly `n` elements**.
    
- If it **was smaller**, new default-initialized elements are added.
    
- If it **was larger**, elements beyond `n` are destroyed.
```cpp
laserCloudOri->resize(feats_down_size);
```
This only:

- **Allocates space** for `feats_down_size` points inside the `laserCloudOri` point cloud.
    
- Initializes them with **default values** (e.g., `x = y = z = intensity = 0`).
    

It **does NOT fill it with real data** from `feats_down_body` or any other source.


# reserve(size_t n)
## Purpose: **Allocates memory** for at least `n` elements but does **not change the size**.

## Meaning:

- Useful when you will `push_back()` elements later.
    
- Avoids repeated memory reallocations.
    
- Faster when you know approximately how many elements you’ll add.
## In context:
```cpp
valid_source_indices->indices.reserve(feats_down_size);
```
This prepares enough memory to store up to `feats_down_size` valid indices, but the size is still zero. You still need to `push_back()` elements into it.

# push_back()
`push_back()` is a C++ method used with containers like `std::vector` or `pcl::PointCloud` to **append a new element to the end** of the container.
## Key Concept:

- It **adds an element** to the container, **increasing its size by 1**.
    
- Unlike `resize()`, it doesn’t preallocate or initialize space — it appends.
---

## Syntax:
```cpp
container.push_back(element);
```
---

## Example with `std::vector`:

```cpp
`std::vector<int> nums; nums.push_back(10); // nums = [10] nums.push_back(20); // nums = [10, 20]`
```
---

## Example with `pcl::PointCloud<pcl::PointXYZ>`:

```cpp
`pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>); pcl::PointXYZ pt; pt.x = 1.0; pt.y = 2.0; pt.z = 3.0; cloud->push_back(pt);  // Adds one point to the cloud`
```

After calling `push_back`, the size of the point cloud increases by one.

# swap()
In C++, `swap()` is a method that **exchanges the contents of two containers or variables**. It's used for efficiency and resource management.
## overview
```cpp
std::vector<int> a = {1, 2, 3};
std::vector<int> b = {4, 5};

a.swap(b);
// Now: a = {4, 5}, b = {1, 2, 3}
```

## Common Use Cases

### 1. **Clear memory efficiently**

Instead of:

```cpp
std::vector<int> v; 
v.clear();  // shrinks size but may not release capacity
```

Use:
```cpp
std::vector<int>().swap(v);  // replace with empty vector
```
This actually **releases memory** because the temporary vector has zero capacity.

### 2. Reset point clouds in PCL
```cpp
PointCloudXYZI().swap(*laserCloudOri);
```
This:
- Replaces `laserCloudOri` with a new, empty point cloud.
- Clears the existing data and **frees memory**.


# 如何找到vector 中的最大值和最小值并返回索引
```cpp
#include <iostream>
#include <vector>
#include <algorithm> // for std::max_element, std::min_element

int main() {
    std::vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6};

    // 找到最大值的迭代器，并计算索引
    auto max_it = std::max_element(vec.begin(), vec.end());
    int max_index = std::distance(vec.begin(), max_it);
    int max_value = *max_it;

    // 找到最小值的迭代器，并计算索引
    auto min_it = std::min_element(vec.begin(), vec.end());
    int min_index = std::distance(vec.begin(), min_it);
    int min_value = *min_it;

    std::cout << "Max value: " << max_value << " at index " << max_index << '\n';
    std::cout << "Min value: " << min_value << " at index " << min_index << '\n';

    return 0;
}
```

# lower_bound()
In this code, `lower_bound` is a standard C++ algorithm from the `<algorithm>` library that performs a **binary search** on a sorted range to find the **first element that is not less than** (i.e., greater than or equal to) a given target value.

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        for (const auto& row: matrix) {
            auto it = lower_bound(row.begin(), row.end(), target);
            if (it != row.end() && *it == target) {
                return true;
            }
        }
        return false;
    }
};

```

