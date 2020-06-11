static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// dfs回溯

class Solution {
    vector<int> res;
    void trackback(TreeNode* root, int num){
        if(root){
            num += root->val;
            if(!root->left && !root->right){
                res.emplace_back(num);
                return ;
            }
            if(root->left) trackback(root->left, num*10);
            if(root->right) trackback(root->right, num*10);
        }
    }
public:
    int sumNumbers(TreeNode* root) {
        trackback(root, 0);
        int ans = 0;
        for(int i = 0; i < res.size(); ++i){
            ans += res[i];
        }
        return ans;
    }
};

// 简洁版

class Solution {
    int helper(TreeNode* root, int i){
        if (!root) return 0;
        int temp = i * 10 + root->val;
        if (!root->left && !root->right) return temp;
        return helper(root->left, temp) + helper(root->right, temp);
    }
public:
    int sumNumbers(TreeNode* root) {
        return helper(root, 0);
    }
};