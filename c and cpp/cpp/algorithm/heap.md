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
1. heapify up
当一个新元素被插入到堆的最后（末尾节点）后，为了维持堆的性质（最大堆或最小堆），需要将其逐层与父节点比较并上移，直到堆性质恢复。
2. heapify down
当堆顶元素被删除（如 `pop()`），通常将最后一个元素移到堆顶。此时可能违反堆的性质，需要将其逐层与子节点比较并下移，直到堆结构合法。