static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// DFS

class Solution {
private:
    bool has;
    void dfs(TreeNode* root, int sum, int s){
        if(root){
            s += root->val;
            if(s == sum && !root->left && !root->right){
                has = true;
                return ;
            }
            dfs(root->left, sum, s);
            dfs(root->right, sum, s);
        }
    }
public:
    bool hasPathSum(TreeNode* root, int sum) {
        has = false;
        dfs(root, sum, 0);
        return has;
    }
};

// 简化

class Solution {
private:
    bool dfs(TreeNode* root, int sum, int s){
        if(!root) return false;
        s += root->val;
        if(s == sum && !root->left && !root->right) return true;
        return dfs(root->left, sum, s) || dfs(root->right, sum, s);
    }
public:
    bool hasPathSum(TreeNode* root, int sum) {
        return dfs(root, sum, 0);
    }
};

// 再简化

class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if(!root) return false;
        if(!root->left && !root->right) return sum - root->val == 0;
        return hasPathSum(root->left, sum-root->val) || hasPathSum(root->right, sum-root->val);
    }
};