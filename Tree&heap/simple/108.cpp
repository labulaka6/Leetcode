static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 二分查找 + 递归

class Solution {
private:
    TreeNode* helper(vector<int>& nums, int l, int r){
        if(l == r) return nullptr;
        int mid = l + (r - l)/2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = helper(nums, l, mid);
        root->right = helper(nums, mid+1, r);
        return root;
    }

public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return helper(nums, 0, nums.size());
    }
};