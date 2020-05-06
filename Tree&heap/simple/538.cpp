static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 迭代
// 中序遍历倒着来

class Solution {
public:
    TreeNode* convertBST(TreeNode* root) {
        stack<TreeNode*> stack;
        TreeNode* p = root;
        int inorder = 0;
        while (!stack.empty() || p != nullptr) {
            while (p != nullptr) {
                stack.push(p);
                p = p->right;
            }
            p = stack.top();
            stack.pop();
            p->val += inorder;
            inorder = p->val;
            p = p->left;
        }
        return root;
    }
};

// 递归

class Solution {
    int n = 0;
    void aux(TreeNode* root){
        if(root){
            aux(root->right);
            root->val += n;
            n = root->val;
            aux(root->left);
        }
    }
public:
    TreeNode* convertBST(TreeNode* root) {
        aux(root);
        return root;
    }
};