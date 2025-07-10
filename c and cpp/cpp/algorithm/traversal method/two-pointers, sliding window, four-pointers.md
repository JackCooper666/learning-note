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

# four-pointers
可以将矩阵看成若干层，首先输出最外层的元素，其次输出次外层的元素，直到输出最内层的元素。

定义矩阵的第 k 层是到最近边界距离为 k 的所有顶点。例如，下图矩阵最外层元素都是第 1 层，次外层元素都是第 2 层，剩下的元素都是第 3 层。

```cpp
[[1, 1, 1, 1, 1, 1, 1], 
[1, 2, 2, 2, 2, 2, 1], 
[1, 2, 3, 3, 3, 2, 1], 
[1, 2, 2, 2, 2, 2, 1], 
[1, 1, 1, 1, 1, 1, 1]]
```

对于每层，从左上方开始以顺时针的顺序遍历所有元素。假设当前层的左上角位于 (top,left)，右下角位于 (bottom,right)，按照如下顺序遍历当前层的元素。

- 从左到右遍历上侧元素，依次为 (top,left) 到 (top,right)。
- 从上到下遍历右侧元素，依次为 (top+1,right) 到 (bottom,right)。
- 如果 left<right 且 top<bottom，则从右到左遍历下侧元素，依次为 (bottom,right−1) 到 (bottom,left+1)，以及从下到上遍历左侧元素，依次为 (bottom,left) 到 (top+1,left)。

遍历完当前层的元素之后，将 left 和 top 分别增加 1，将 right 和 bottom 分别减少 1，进入下一层继续遍历，直到遍历完所有元素为止。
![[four-pointers.png]]

```cpp
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.size() == 0 || matrix[0].size() == 0) {
            return {};
        }

        int rows = matrix.size(), columns = matrix[0].size();
        vector<int> order;
        int left = 0, right = columns - 1, top = 0, bottom = rows - 1;
        while (left <= right && top <= bottom) {
            for (int column = left; column <= right; column++) {
                order.push_back(matrix[top][column]);
            }
            for (int row = top + 1; row <= bottom; row++) {
                order.push_back(matrix[row][right]);
            }
            if (left < right && top < bottom) {
                for (int column = right - 1; column > left; column--) {
                    order.push_back(matrix[bottom][column]);
                }
                for (int row = bottom; row > top; row--) {
                    order.push_back(matrix[row][left]);
                }
            }
            left++;
            right--;
            top++;
            bottom--;
        }
        return order;
    }
};

```