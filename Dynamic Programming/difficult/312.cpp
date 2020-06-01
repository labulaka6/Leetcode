static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();


class Solution {
public:
    int maxCoins(vector<int>& nums) {
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        int n = nums.size();
        // dp[i][j]表示第i至第j个元素这个区间能获得的最大硬币数
        vector<vector<int>> dp(n, vector<int> (n, 0));
        for(int r = 2; r < n; ++r)            // r为区间长度
            for(int i = 0; i < n-r; ++i){    // i为左区间
                int j = i + r;            // j为右区间
                for(int k = i + 1; k < j; ++k)
                    dp[i][j] = max(dp[i][j], dp[i][k] + dp[k][j] + nums[i]*nums[k]*nums[j]);
            }
        // for (int left = n - 2; left > -1; left--)
        //     for (int right = left + 2; right < n; right++) {
        //         for (int i = left + 1; i < right; ++i)
        //             dp[left][right] = max(dp[left][right], nums[left] * nums[i] * nums[right] + dp[left][i] + dp[i][right]);
        //     }
        return dp[0][n-1];
    }
};
