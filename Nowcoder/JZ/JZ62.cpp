static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 中序遍历
// 搜索二叉树中序遍历为升序序列
// 稍有不同，Leetcode输出第k大，Nowcode输出第k小

class Solution {
    void reverse(TreeNode* root, vector<int>& nums){
        if(root){
            reverse(root->left, nums);
            nums.emplace_back(root->val);
            reverse(root->right, nums);
        }
    }
public:
    int kthLargest(TreeNode* root, int k) {
        vector<int> nums;
        reverse(root, nums);
        int len = nums.size();
        return nums[len-k];
    }
};