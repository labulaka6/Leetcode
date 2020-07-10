static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
    void reverse(TreeNode* root, vector<int>& nums){
        if(root){
            reverse(root->left, nums);
            nums.emplace_back(root->val);
            reverse(root->right, nums);
        }
    }
public:
    int kthSmallest(TreeNode* root, int k) {
        vector<int> nums;
        reverse(root, nums);
        int len = nums.size();
        return nums[k-1];
    }
};