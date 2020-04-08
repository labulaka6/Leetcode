// 动态规划
// dp[i]为偷窃前i座房屋的最大收益
// 因为不能偷窃连续的两座房屋，所以dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
static const auto _ = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size() == 0) return 0;  // 空数组
        else if(nums.size() == 1) return nums[0];  //因为下面出现了nums[1]，所以需要判断
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        for(int i = 2; i < nums.size(); i++){
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
        }
        return *max_element(dp.begin(), dp.end());
    }
};
// 基于上面的解法，其实只需要两个变量(记录前两步的值)，以及一个用于临时储存的变量
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        else if(nums.size() == 1) return nums[0];
        int dp = nums[0];   //往前两步
        int maxdp = max(nums[0], nums[1]);   //往前一步
        for(int i = 2; i < nums.size(); i++){
            int temp = maxdp;
            maxdp = max(dp + nums[i], maxdp);
            dp = temp;
        }
        return maxdp;
    }
};

// 进一步简化
class Solution {
public:
    int rob(vector<int>& nums) {
        int dp = 0;
        int maxdp = 0;
        for(int x : nums){
            int temp = maxdp;
            maxdp = max(dp + x, maxdp);
            dp = temp;
        }
        return maxdp;
    }
};
