static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 动态规划
// dp[i][0] 为 第i天没有持有股票的最高收益
// dp[i][1] 为 第i天持有股票的最高收益
// 则状态转移方程为：
// dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i])
// dp[i][1] = max(dp[i-1][1], dp[i-2][0] - prices[i])

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n < 2) return 0;
        int dp[n][2];
        dp[0][0] = 0;
        dp[0][1] = 0 - prices[0];
        dp[1][0] = max(dp[0][0], dp[0][1] + prices[1]);
        dp[1][1] = max(dp[0][1], dp[0][0] - prices[1]);
        for(int i = 2; i < n; ++i){
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i]);
            dp[i][1] = max(dp[i-1][1], dp[i-2][0] - prices[i]);
        }
        return dp[n-1][0]
    }
};

// 优化空间复杂度

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int dp_i_0 = 0, dp_i_1 = INT_MIN;
        int dp_pre_0 = 0;
        for(int i = 0; i < n; ++i){
            int tmp = dp_i_0;
            dp_i_0 = max(dp_i_0, dp_i_1 + prices[i]);
            dp_i_1 = max(dp_i_1, dp_pre_0 - prices[i]);
            dp_pre_0 = tmp;
        }
        return dp_i_0;
    }
};