# full binary tree
每个节点要么是**叶子节点**（无子节点），要么恰好有**两个子节点**（即左、右子树都不为空）。
```markdown
        1
      /   \
     2     3
    / \   / \
   4   5 6   7
```

# complete binary tree
except the last layer, other layers should be full, but the leaves of the last layer should be continuous like this 
若将这棵树的节点从上到下、从左到右编号为 1、2、3……n，则**所有编号 ≤ n 的位置都有节点**，即节点排列紧凑，没有“空洞”
```markdown
        1
      /   \
     2     3
    / \   /
   4   5 6
```
# binary search tree
unlike the complete binary tree and full binary tree, the binary search tree does not have the structure requirement
一棵二叉搜索树是满足以下条件的**二叉树**：
- 每个节点最多有两个子节点（即左子树和右子树）；
- **对于任意一个节点**：
    - **左子树中所有节点的值都小于该节点的值**；
    - **右子树中所有节点的值都大于该节点的值**；
- 每棵子树本身也是一棵二叉搜索树（具有递归结构）。
```markdown
       5
     /   \
    3     7
   / \   / \
  2  4  6  8
```
# balanced binary search tree
平衡二叉搜索树不仅满足普通 BST 的性质：
- 左子树所有节点的值 < 当前节点的值；
- 右子树所有节点的值 > 当前节点的值；
- 每棵子树也都是一棵 BST。
还要求整棵树在结构上要尽可能**平衡**，即：
树中任意一个节点的左右子树的高度差不能超过1。

对于任意一个节点 `N`，其子树高度定义如下：
- 如果 `N` 是**空节点（null）**，那么高度为 `-1`（有些定义为 `0`，看具体场景）；
- 如果 `N` 是**叶子节点**（没有子节点），那么高度为 `0`；
- 否则，高度为：
$$
height(N) = 1 + max(height(N.left), height(N.right))
$$
树的高度可以看作是：

> **从该节点到最远叶子节点的最大路径长度（以边数计）**

```markdown
        A
       / \
      B   C
     /     \
    D       E
```
- 节点 D 和 E 是叶子节点，高度 = 0
- 节点 B 的高度 = 1（因为左子树 D 高度为 0）
- 节点 C 的高度 = 1（因为右子树 E 高度为 0）
- 节点 A 的高度 = 1 + max(1, 1) = 2

# the storage method of binary tree
**二叉树的链式存储结构**是一种使用**指针链接**的方式来存储二叉树节点的结构。每个节点包含三个部分：**数据域**、**左孩子指针**和**右孩子指针**。
1. 声明一个树节点结构体
```cpp
// 二叉树节点定义
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    // 构造函数
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

```
2. 创建节点
```cpp
TreeNode *node1 = TreeNode(1);
TreeNode *node2 = TreeNode(2);
TreeNode *node3 = TreeNode(3);
TreeNode *node4 = TreeNode(4);
TreeNode *node5 = TreeNode(5);
TreeNode *node6 = TreeNode(6);
TreeNode *node7 = TreeNode(7);
```
3. 连接节点
```cpp
node1->left = node2;
node1->right = node3;
node2->left = node4;
node2->right = node5;
node3->left = node6;
node3->right = node7;
//和链表一样，知道第一个节点，就可以搜索所有的节点，所以我们可以用根部节点来代表整个二叉树
//即TreeNode* node1代表了整棵二叉树
```

