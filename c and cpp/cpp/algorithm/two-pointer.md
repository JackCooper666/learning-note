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

