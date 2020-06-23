static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 递归

class Solution {
public:
    TreeNode* mirrorTree(TreeNode* root) {
        if(!root) return nullptr;
        TreeNode* left = mirrorTree(root->left);
        TreeNode* right = mirrorTree(root->right);
        root->left = right;
        root->right = left;
        return root;
    }
};

// 递归2

class Solution {
    void tree(TreeNode* root){
        if(root){
            tree(root -> left);
            // TreeNode* tem = root -> left;
            // root -> left = root -> right;
            // root -> right = tem;
            swap(root -> left, root -> right);
            // 上边的 invertTree(root -> left) 已经将左子树全部转换
            // 此时的左子树即原来的右子树
            tree(root -> left);
        }
    }
public:
    TreeNode* mirrorTree(TreeNode* root) {
        tree(root);
        return root;
    }
};