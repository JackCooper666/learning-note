```cpp
int maxDepth(TreeNode* root){
if(root == nullptr) return 0;
queue<TreeNode* > Q;
Q.push(root);
int ans = 0;
while(!Q.empty()){
int sz = Q.size();
while(sz > 0){
TreeNode* node = Q.front();
Q.pop();
if(node->left) Q.push(node->left);
if(node->right) Q.push(node->right);
sz--;
}
ans++;
}
return ans;
}
```
### breadth-first search
```cpp
#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

struct TreeNode{
int data;
struct TreeNode* left;
struct TreeNode* right;
TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};
vector<int> breadthfirstsearch(TreeNode* root) {
vector<int> result;
queue<TreeNode*> q;
if (!root) return result; // 如果根节点为空，返回空结果
else {
q.push(root); // 将根节点入队
}
while(!q.empty()){
int size = q.size(); // 获取当前队列的大小
while(size --){
TreeNode* node = q.front();
q.pop(); // 弹出队列的前端节点
result.push_back(node->data); // 将节点值添加到结果中
if(node->left){
q.push(node->left); // 如果左子节点存在，将其入队
}
if(node->right){
q.push(node->right); // 如果右子节点存在，将其入队
}
}
}
return result; // 返回结果向量
}
int main(){
// 创建一个简单的二叉树
TreeNode* node1 = new TreeNode(1);
TreeNode* node2 = new TreeNode(2);
TreeNode* node3 = new TreeNode(3);
TreeNode* node4 = new TreeNode(4);
TreeNode* node5 = new TreeNode(5);
node1->left = node2;
node1->right = node3;
node2->left = node4;
node2->right = node5;
// 执行广度优先搜索
vector<int> result = breadthfirstsearch(node1);
// 输出结果
for(int i = 0; i < result.size(); i++){
cout << result[i] << " ";
}
cout << endl;
// 释放内存
delete node1;
delete node2;
delete node3;
delete node4;
delete node5;
// 返回0表示程序正常结束
cout << "Program finished successfully." << endl;
return 0; // 返回0表示程序正常结束
}
