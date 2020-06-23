static const auto _  = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// DFS - 回溯

class Solution {
    vector<vector<int>> res;
    int flag;
    void helper(TreeNode* root, int sum, vector<int> tmp){
        if(root){
            sum += root->val;
            tmp.emplace_back(root->val);
            if(sum == flag && !root->left && !root->right){
                res.emplace_back(tmp);
                return ;
            }
            if(root->left) helper(root->left, sum, tmp);
            if(root->right) helper(root->right, sum, tmp);
        }
    }

public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        flag = sum;
        vector<int> tmp;
        helper(root, 0, tmp);
        return res;
    }
};