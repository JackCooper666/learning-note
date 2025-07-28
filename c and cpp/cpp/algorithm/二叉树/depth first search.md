``` cpp
int maxDepth(TreeNode* root) {
if(root == nullptr) return 0;
else{
return max(maxDepth(root->left),maxDepth(root->right)) + 1;
}
}
```