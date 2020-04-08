// 动态规划：
// dp[i]为以nums[i]为最后一位的子数组的最大和
// dp[i]只与dp[i - 1]与nums[i]有关

static const auto _ = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        vector<int> dp(n, 0);
        dp[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            dp[i] = max(nums[i], dp[i - 1] + nums[i]);
        }
        return *max_element(dp.begin(), dp.end());
    }
};