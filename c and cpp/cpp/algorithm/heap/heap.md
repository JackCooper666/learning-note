# definition 
heap is an complete binary tree
# heap order property
1. min heap
the root should smaller than the right and left leaves
```markdown
		2
	  /   \
	 3     4
	/ \   / \
   5   6 5   6
```
2. max heap
the root should larger than the right and left leaves
```markdown
		3
	  /   \
	 1     2
    / \   / 
   0   0 1   
```

# basic operator
used to build min heap and max heap, and the heapsort
## heapify up
将某个节点逐层与父节点比较并上移，直到堆性质恢复。
### min heap
原堆（小顶堆）：
```Markdown
       2
      / \
     5   3
    /
   7
```
插入新元素 `1`，放在最后一层：
```Markdown
       2
      / \
     5   3
    / 
   7
  /
 1   ← 插入
```

**上滤过程**：
- `1 < 7` → 交换
- `1 < 5` → 交换
- `1 < 2` → 交换
```markdown
       1
      / \
     2   3
    / 
   7
  /
 5
```

大顶堆（Max Heap）：
```markdown
       8
      / \
     6   7
    /
   4
```
插入 `9`：
```markdown
       8
      / \
     6   7
    / 
   4
  /
 9   ← 插入
```
**上滤过程**：
- `9 > 4` → 交换
- `9 > 6` → 交换
- `9 > 8` → 交换  
    最终结果：
```markdown
       9
      / \
     8   7
    / 
   6
  /
 4
```

## heapify down
将某个节点逐层与子节点比较并下移，直到堆结构合法。
小顶堆（Min Heap）:
```markdown
       1
      / \
     3   5
    / \
   4   6
```
删除 1 → 用 6 替代堆顶：
```markdown
       6
      / \
     3   5
    / \
   4
```
**下滤过程**：
- `6 > 3` → 交换
- `6 > 4` → 交换  
    最终堆：
```markdown
       3
      / \
     4   5
    / 
   6
```

# heap construct
## ✅ A. Build a Heap Using **Heapify Up**

### 🔼 Idea: insert elements one by one, then "bubble up" to fix the heap

### Example: Build Max Heap from `[4, 2, 7, 1, 3]`

**Step 1:** Start with an empty array. Insert `4`, heap = `[4]`  
**Step 2:** Insert `2` → `[4, 2]` → OK (2 < 4)  
**Step 3:** Insert `7` → `[4, 2, 7]` → 7 > 4 → swap → `[7, 2, 4]`  
**Step 4:** Insert `1` → `[7, 2, 4, 1]` → OK  
**Step 5:** Insert `3` → `[7, 2, 4, 1, 3]` → 3 > 2 → swap → `[7, 3, 4, 1, 2]`

**Max Heap built using heapify up!**
### C++ Code (Max Heap):
```cpp
void heapifyUp(vector<int>& heap, int i) {
    while (i > 0 && heap[i] > heap[(i - 1) / 2]) {
        swap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void buildHeapUp(vector<int>& data) {
    vector<int> heap;
    for (int val : data) {
        heap.push_back(val);
        heapifyUp(heap, heap.size() - 1);
    }
}
```
## ✅ B. Build a Heap Using **Heapify Down** (More Efficient)

### 🔽 Idea: treat array as a complete binary tree, and fix each subtree **from the middle to the top**

### Step-by-step for **Max Heap**:
Given array: `[4, 2, 7, 1, 3]`  
We start from the last non-leaf node: index = `(n/2 - 1)` and do `heapifyDown`
1. Start at index 1 (`2`) → has children `1` and `3` → max child = `3` → swap → `[4, 3, 7, 1, 2]`
2. Index 0 (`4`) → children `3`, `7` → max child = `7` → swap → `[7, 3, 4, 1, 2]`
Final Max Heap: `[7, 3, 4, 1, 2]`
### C++ Code (Max Heap):
```cpp
void heapifyDown(vector<int>& heap, int i, int n) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && heap[left] > heap[largest]) largest = left;
    if (right < n && heap[right] > heap[largest]) largest = right;
    if (largest != i) {
        swap(heap[i], heap[largest]);
        heapifyDown(heap, largest, n);
    }
}

void buildHeapDown(vector<int>& heap) {
    int n = heap.size();
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapifyDown(heap, i, n);
    }
}
```

# priority queue
the min heap is the best option to do this
![[priority_queue.png]]
1. build min heap
2. pop the root of the tree
3. then put the last node into the root, then heapify down
4. get a new min heap
5. pop the root of the tree
6. repeat the step 3.-step 5.
```cpp
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    priority_queue<int, vector<int>, greater<int>> minPQ;  // Min heap

    minPQ.push(5);
    minPQ.push(2);
    minPQ.push(8);
    minPQ.push(4);

    cout << "Top 1: " << minPQ.top() << endl;  // Should be 2
    minPQ.pop();

    cout << "Top 2: " << minPQ.top() << endl;  // Should be 4
    minPQ.pop();

    return 0;
}
```

# heapsort
the max heap is the best option to do this
**Step-by-step**:
1. Build a **max heap** from the array.
2. Swap the first (largest) element with the last.
3. Reduce heap size by 1, and **heapify down** from the root.
4. Repeat until sorted.
### 🧮 Example:
Unsorted array: `[4, 10, 3, 5, 1]`
1. Build max heap: `[10, 5, 3, 4, 1]`
2. Swap 10 ↔ 1: `[1, 5, 3, 4, 10]`
3. Heapify `[1, 5, 3, 4]` → `[5, 4, 3, 1, 10]`
4. Swap 5 ↔ 1: `[1, 4, 3, 5, 10]`  
    ... and so on.
Final result: `[1, 3, 4, 5, 10]`

```cpp
#include <iostream>
#include <vector>
using namespace std;

void heapifyDown(vector<int>& arr, int n, int i) {
    int largest = i;         // Initialize largest as root
    int left = 2 * i + 1;    // Left child
    int right = 2 * i + 2;   // Right child

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapifyDown(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    // 1. Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyDown(arr, n, i);

    // 2. Extract elements from heap one by one
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);            // Move max to end
        heapifyDown(arr, i, 0);          // Re-heapify remaining
    }
}

int main() {
    vector<int> arr = {4, 10, 3, 5, 1};

    heapSort(arr);

    cout << "Sorted array: ";
    for (int val : arr)
        cout << val << " ";  // Output: 1 3 4 5 10
    cout << endl;

    return 0;
}

```