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
    //     if(node != nullptr){
    //         // 如果当前节点不为空，先将其压入栈中，并移动到左子节点
    //         st.push(node);
    //         node = node->left;
    //     }
    //     else{
    //         // 如果当前节点为空，弹出栈顶节点并访问它
    //         node = st.top();
    //         st.pop();
    //         if(node != nullptr) {
    //             res.push_back(node->data); // 访问当前节点
    //             node = node->right; // 移动到右子节点
    //         }
    //     }

    // }
    // return res; // 返回中序遍历结果
    // while (node != nullptr || !st.empty()) {
    //     while (node != nullptr) {
    //         st.push(node);           // push left ancestors
    //         node = node->left;
    //     }

    //     node = st.top();             // backtrack
    //     st.pop();
    //     res.push_back(node->data);   // visit the node
    //     node = node->right;          // go to right subtree
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
