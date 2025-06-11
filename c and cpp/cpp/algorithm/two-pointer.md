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

# left-right pointers
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

