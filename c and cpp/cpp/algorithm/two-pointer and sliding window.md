常用双指针思想
双指针是解数组、链表题中最常见的思想之一。总的来说有四大用途：

	快慢指针：一个指针移动两步，一个指针移动一步。或者两指针移动起点相差K。
	
	头尾指针：指针一头一尾同时向内靠近。最常见的就是翻转字符串。
	
	栅栏指针：两个指针仿佛围成一个栅栏，一个指针的一侧全部存放符合要求的节点，另一个指针负责遍历寻找。常用于要求原地处理的题目。
	
	滑动窗口：两个指针一前一后形成一个窗口，不满足条件时前面的不停扩大窗口，满足时后面指针前进，缩小窗口，由可行解寻找最优解。

# slow-fast pointers
- Use a **slow pointer (`slow`)** to track the position where the next valid element should be placed.
- Use a **fast pointer (`fast`)** to scan through the array.
- For each element, check if it should be kept (i.e., it hasn't appeared more than twice consecutively).
- If it should be kept, copy it to the `slow` position and increment `slow`.

```cpp
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() <= 2) {
            return nums.size(); // No need to process if size is 2 or less
        }
        int slow = 2; // Start from the third element
        for (int fast = 2; fast < nums.size(); fast++) {
            if (nums[fast] != nums[slow - 2]) { // Check if current element can be kept
                nums[slow] = nums[fast]; // Overwrite the slow position
                slow++; // Move slow forward
            }
            // Else, skip the element (it's a duplicate beyond the allowed two)
        }
        return slow; // New length of the array
    }
};
```

# left-right pointers (head-tail pointers)
e.g.
给你一个下标从 **1** 开始的整数数组 `numbers` ，该数组已按 **非递减顺序排列**  ，请你从数组中找出满足相加之和等于目标数 `target` 的两个数。如果设这两个数分别是 `numbers[index1]` 和 `numbers[index2]` ，则 `1 <= index1 < index2 <= numbers.length` 。

以长度为 2 的整数数组 `[index1, index2]` 的形式返回这两个整数的下标 `index1` 和 `index2`。

你可以假设每个输入 **只对应唯一的答案** ，而且你 **不可以** 重复使用相同的元素。

你所设计的解决方案必须只使用常量级的额外空间。

1. **双指针法**：因为数组是已经排序的，我们可以使用两个指针，一个指向数组的起始位置（左指针），另一个指向数组的末尾位置（右指针）。
    
2. **比较和调整指针**：
    
    - 如果当前两个指针指向的元素之和等于目标值，直接返回它们的索引（注意题目要求索引从 1 开始）。
        
    - 如果和小于目标值，说明需要更大的数，因此左指针右移。
        
    - 如果和大于目标值，说明需要更小的数，因此右指针左移。
        
3. **终止条件**：当左指针超过右指针时，循环结束。
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0;
        int right = numbers.size() - 1;
        
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum == target) {
                return {left + 1, right + 1};
            } else if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
        
        return {};
    }
};
```

# window

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