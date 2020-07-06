static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 递归 - 自顶向下
// 先序遍历

class Solution {
private:
    int depth(TreeNode* root){
        if(!root) return 0;
        return max(depth(root->left), depth(root->right)) + 1;
    }
public:
    bool isBalanced(TreeNode* root) {
        if(!root) return true;
        return abs(depth(root->left) - depth(root->right)) <= 1 && isBalanced(root->left) && isBalanced(root->right);
    }
};

// 递归 - 自底向上
// 后序遍历

class Solution {
private:
    int recur(TreeNode* root){
        if (!root) return 0;
        int left = recur(root->left);
        if(left == -1) return -1;
        int right = recur(root->right);
        if(right == -1) return -1;
        return abs(left - right) < 2 ? max(left, right) + 1 : -1;
    }
public:
    bool isBalanced(TreeNode* root) {
       return recur(root) != -1;
    }
};
