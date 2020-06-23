// 递归遍历

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

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
    TreeNode* invertTree(TreeNode* root) {
        tree(root);
        return root;
    }
};

// 递归遍历另一种写法

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) {
            return nullptr;
        }
        TreeNode* right = invertTree(root->right);
        TreeNode* left = invertTree(root->left);
        root->left = right;
        root->right = left;
        return root;
    }
};

// 本题也可以用迭代来解
// 具体解法与 617. 合并二叉树 差别不大
// 不再赘述