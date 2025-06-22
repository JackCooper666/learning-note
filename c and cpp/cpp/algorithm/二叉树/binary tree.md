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

# traverse binary tree

## depth-first search
### preorder traversal
中左右
firstly traverse the root then traverse the left subtree and then the right subtree
```markdown
		5
	  /   \
	 4     6
    / \   / \
   1  2  7   8
```
traversal result:
5->4->1->2->6->7->8
1. by recursion
2. by iteration
### inorder traversal
左中右
firstly traverse the left subtree then the root and then the right subtree
```markdown
		5
	  /   \
	 4     6
    / \   / \
   1  2  7   8
```
traversal result:
1->4->2->5->7->6->8
1. by recursion
2. by iteration
### postorder traversal
左右中
firstly traverse the left subtree, then the right subtree and then the root
```markdown
		5
	  /   \
	 4     6
    / \   / \
   1  2  7   8
```
traversal result:
1->2->4->7->8->6->5
1. by recursion
2. by iteration

## breadth-first search
### level_order traversal
1. by iteration

## code
### depth-first search
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;
struct TreeNode {
int data;
TreeNode* left;
TreeNode* right;
// 构造函数
TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

class depth_first_search {
public:
// binary tree traversal methods by recursion
void perorder_traversal(TreeNode* node, vector<int>& result);
void inorder_traversal(TreeNode* node, vector<int>& result);
void postorder_traversal(TreeNode* node, vector<int>& result);
// binary tree traversal methods by iteration
vector<int> perorder_traversal_iterative(TreeNode* node);
vector<int> inorder_traversal_iterative(TreeNode* node);
vector<int> postorder_traversal_iterative(TreeNode* node);
};

void depth_first_search::perorder_traversal(TreeNode* node, vector<int>& result) {
//base case
if(node == nullptr){
return;
}
else{
result.push_back(node->data); // 访问当前节点
perorder_traversal(node->left, result); // 递归访问左子树
perorder_traversal(node->right, result); // 递归访问右子树
}
}

void depth_first_search::inorder_traversal(TreeNode* node, vector<int>& result) {
//base case
if(node == nullptr){
return;
}
// recursion case
else{
inorder_traversal(node->left, result); // 递归访问左子树
result.push_back(node->data); // 访问当前节点
inorder_traversal(node->right, result); // 递归访问右子树
}
}
void depth_first_search::postorder_traversal(TreeNode* node, vector<int>& result) {
//base case
if(node == nullptr){
return;
}
// recursion case
else{
postorder_traversal(node->left, result); // 递归访问左子树
postorder_traversal(node->right, result); // 递归访问右子树
result.push_back(node->data); // 访问当前节点
}
}

vector<int> depth_first_search::perorder_traversal_iterative(TreeNode* node) {
vector<int> res;
stack<TreeNode*> st;
if(node == nullptr) {
return res; // 如果节点为空，返回空向量
}
st.push(node); // 将根节点压入栈中
while(!st.empty()){
node = st.top(); // 获取栈顶节点
st.pop(); // 弹出栈顶节点
if(node != nullptr) {
res.push_back(node->data); // 访问当前节点
}
else continue;
st.push(node->right);
st.push(node->left);
}
return res; // 迭代方法未实现，返回空向量
}
vector<int> depth_first_search::inorder_traversal_iterative(TreeNode* node) {
vector<int> res;
stack<TreeNode*> st;
// // st.push(node); // 将根节点压入栈中
// while(!st.empty()){
// if(node != nullptr){
// // 如果当前节点不为空，先将其压入栈中，并移动到左子节点
// st.push(node);
// node = node->left;
// }
// else{
// // 如果当前节点为空，弹出栈顶节点并访问它
// node = st.top();
// st.pop();
// if(node != nullptr) {
// res.push_back(node->data); // 访问当前节点
// node = node->right; // 移动到右子节点
// }
// }
// }
// return res; // 返回中序遍历结果
// while (node != nullptr || !st.empty()) {
// while (node != nullptr) {
// st.push(node); // push left ancestors
// node = node->left;
// }
// node = st.top(); // backtrack
// st.pop();
// res.push_back(node->data); // visit the node
// node = node->right; // go to right subtree
// }

while(node != nullptr || !st.empty()) {
while(node != nullptr){
st.push(node); // 将当前节点压入栈中
node = node->left; // 移动到左子节点
}
node = st.top();
st.pop(); // 弹出栈顶节点
if(node != nullptr) {
res.push_back(node->data); // 访问当前节点
}
node = node->right; // 移动到右子节点
}
return res;
}
vector<int> depth_first_search::postorder_traversal_iterative(TreeNode* node) {
vector<int> res;
stack<TreeNode*> st;
if(node == nullptr) {
return res; // 如果节点为空，返回空向量
}
st.push(node); // 将根节点压入栈中
while(!st.empty()){
node = st.top();
st.pop();
if(node != nullptr) {
res.push_back(node->data); // 访问当前节点
}
else continue;
st.push(node->left); // 先将左子树压入栈中
st.push(node->right); // 再将右子树压入栈中
}
int left = 0,right = res.size() - 1;
// 反转结果向量以实现后序遍历
while(left < right) {
swap(res[left], res[right]);
left++;
right--;
}
return res; // 返回后序遍历结果
}

int main(){
// 创建一个简单的二叉树
TreeNode* node1 = new TreeNode(5);
TreeNode* node2 = new TreeNode(4);
TreeNode* node3 = new TreeNode(6);
TreeNode* node4 = new TreeNode(2);
TreeNode* node5 = new TreeNode(1);
TreeNode* node6 = new TreeNode(3);
node1->left = node2;
node1->right = node3;
node2->left = node4;
node2->right = node5;
node3->left = node6;
vector<int> result; // 用于存储遍历结果
// 创建深度优先搜索对象
depth_first_search dfs;
// 执行前序遍历
dfs.perorder_traversal(node1, result);
// 输出结果
cout << "前序遍历结果: ";
for(int val : result) {
cout << val << " ";
}
cout << endl;
// 清空结果向量
result.clear();
// 执行中序遍历
dfs.inorder_traversal(node1, result);
// 输出结果
cout << "中序遍历结果: ";
for(int val : result) {
cout << val << " ";
}
cout << endl;
// 清空结果向量
result.clear();
// 执行后序遍历
dfs.postorder_traversal(node1, result);
// 输出结果
cout << "后序遍历结果: ";
for(int val : result) {
cout << val << " ";
}
cout << endl;
// 清空结果向量
result.clear();
// 执行迭代前序遍历
vector<int> iterative_result = dfs.perorder_traversal_iterative(node1);
// 输出结果
cout << "迭代前序遍历结果: ";
for(int val : iterative_result) {
cout << val << " ";
}
cout << endl;
// 清空结果向量
iterative_result.clear();
// 执行迭代中序遍历
iterative_result = dfs.inorder_traversal_iterative(node1);
// 输出结果
cout << "迭代中序遍历结果: ";
for(int val : iterative_result) {
cout << val << " ";
}
cout << endl;
// 清空结果向量
iterative_result.clear();
// 执行迭代后序遍历
iterative_result = dfs.postorder_traversal_iterative(node1);
// 输出结果
cout << "迭代后序遍历结果: ";
for(int val : iterative_result) {
cout << val << " ";
}
cout << endl;
// 清空结果向量
iterative_result.clear();
// 释放内存
delete node1;
delete node2;
delete node3;
delete node4;
delete node5;
// 返回0表示程序正常结束
cout << "程序正常结束" << endl;
cout << "释放内存" << endl;
return 0;
}
```
### breadth-first search