// 动态规划：
// dp[i]为到第i个台阶的所有方式的数目
// 因为步长为1或者2，所以dp[i]只与dp[i -1]与dp[i - 2]有关
static const auto _ = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int climbStairs(int n) {
        if(n == 0) return 0;
        else if(n == 1) return 1;
        else if(n == 2) return 2;
        vector<int> dp(n + 1, 0);
        dp[1] = 1;
        dp[2] = 2;
        for(int i = 3; i <= n; i++){
            dp[i] = dp[i - 1] + dp[i - 2]; // 步长为1或者2
        }
        return dp[n];
    }
};