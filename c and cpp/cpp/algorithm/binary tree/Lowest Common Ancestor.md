当我们处理树上点与点关系的问题时（例如，最简单的，树上两点的**距离**），常常需要获知树上两点的**最近公共祖先**（Lowest Common Ancestor，LCA）。如下图所示：现在A点的深度比B点深，所以我们先让B点往上“爬”，爬到与A点深度相等为止。然后A点和B点再一起往上爬，直到两点相遇，那一点即为LCA：

![[v2-99457646a2f9b511f82dd244eb76ba2c_r.png]]

给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

[百度百科](https://baike.baidu.com/item/%E6%9C%80%E8%BF%91%E5%85%AC%E5%85%B1%E7%A5%96%E5%85%88/8918834?fr=aladdin)中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（**一个节点也可以是它自己的祖先**）。”
```cpp
class Solution {

public:

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

TreeNode* lca = lcasearch(root, p, q);

return lca;

}

TreeNode* lcasearch(TreeNode* root, TreeNode* p, TreeNode* q){

if(root == p || root == q) return root;

if(root == nullptr) return nullptr;

TreeNode* left = lcasearch(root->left, p, q);

TreeNode* right = lcasearch(root->right,p,q);

if(left && right) {

return root;

}

else if(left){

return left;

}

else if(right){

return right;

}

else{

return nullptr;

}

}

};
```