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

// dp[i] 只与 dp[i-1] 和 dp[i-2]有关
// 可优化空间复杂度为常数级别

class Solution {
public:
    int climbStairs(int n) {
        if(n < 2) return 1;
        int a = 1, b = 2;
        int ans = 2;
        for(int i = 2; i < n; ++i){
            ans = a + b;
            a = b;
            b = ans;
        }
        return ans;
    }
};