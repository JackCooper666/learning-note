list consists of nodes
# single direction list
node consist of its data and a pointer pointing to the address of the next node.
![[list.png]]
the advantages of the the list is that:
1. user can insert or delete nodes at any position

the disadvantages of the list is that:
1. the traversal speed is slower than the that of the array
2. space consumption is larger than that of the array

# the list in the STL
The STL's list is bio-direction list.
The node of it consists of three things: the data, the next pointer pointing to the address of the next node, the previous pointer pointing to the address of the previous node.
![[bio_direction_list.jpg]]

`push_front()`: push node at the top
`pop_front()`: pop the node at the top
`front()`: get the node at the top
`push_back()`: push node at the end
`pop_back()`: pop the node at the end
`back()`: get the node at the end

由于链表的存储方式并不是连续的内存空间，因此链表list中的迭代器只支持前移和后移，属于**双向迭代器**
## construct list
```
```
