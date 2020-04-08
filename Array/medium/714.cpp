// 动态规划

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// dp[i][k][0]到代表第i天进行了k次交易，此时手中没有股票的最大利润(1代表手中有股票)
// dp[i][k][1] = max(dp[i-1][k][1], dp[i-1][k-1][0] - price[i-1])
// dp[i][k][0] = max(dp[i-1][k][0], dp[i-1][k][1] + price[i] - fee)
// k = infinity 所以 k-1 = infinity k对状态转移方程没有影响，可以舍去
class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        int dp[n][2];
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 0;
        dp[0][1] = -prices[0];
        for(int i = 1; i < n; ++i){
            dp[i][1] = max(dp[i-1][1], dp[i-1][0] - prices[i]);
            dp[i][0] = max(dp[i-1][0], dp[i-1][1] + prices[i] - fee);
        }
        return dp[n-1][0];

    }
};

// 进一步简化，只需要两个变量即可

class Solution {
public:
    int maxProfit(vector<int>& prices, int fee) {
        int dp_0 = 0, dp_1 = -prices[0];
        for(int i = 1; i < prices.size(); ++i){
            int tem = dp_1;
            dp_1 = max(dp_1, dp_0 - prices[i]);
            dp_0 = max(dp_0, dp_1 + prices[i] - fee);
        }
        return dp_0;
    }
};