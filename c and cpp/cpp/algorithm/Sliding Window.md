滑动窗口是一种**用于处理数组/字符串子区间问题的高效算法技巧**，通过维护一个动态的“窗口”来避免暴力枚举，将时间复杂度从 **O(n²) 优化到 O(n)**。

---

## **1. 核心思想**

- **窗口定义**：在数组/字符串中维护一个**连续的区间** `[left, right]`，通过调整 `left` 和 `right` 来滑动窗口。
    
- **关键操作**：
    
    - **扩大窗口**（`right++`）：寻找可行解。
        
    - **收缩窗口**（`left++`）：优化可行解。
        
- **适用场景**：子串、子数组的最优解问题（如“最小覆盖子串”、“最长无重复子串”）。
    

---

## **2. 算法框架（C++）**
```cpp
void slidingWindow(string s) {
    int left = 0, right = 0;  // 窗口边界
    unordered_map<char, int> window; // 窗口内字符的统计

    while (right < s.size()) {
        char c = s[right];
        window[c]++;          // 扩大窗口
        right++;

        while (window[c] > 1) { // 满足收缩条件
            char d = s[left];
            window[d]--;       // 收缩窗口
            left++;
        }
        // 在此更新答案（如最大/最小长度）
    }
}
```