```cpp
std::vector<int> table(26, 0);
```
1. **`std::vector<int>`**
    
    - A dynamic array that can store integers (`int`).
        
2. **`table(26, 0)`**
    
    - **`26`**: The size of the vector (26 elements).
        
    - **`0`**: The initial value for all 26 elements.


# reresize(size_t n)

## Purpose: **Changes the actual size** of the container.

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