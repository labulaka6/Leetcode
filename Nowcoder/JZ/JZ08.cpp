static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 动态规划
// dp[i] 为i阶台阶共有多少种跳法
// 初始状态 dp[0] = 1, dp[1] = 1
// 状态转移方程为 dp[i] = dp[i-1] + dp[i-2]
// dp[i] 只与 dp[i-1] 和 dp[i-2] 有关
// 可优化空间复杂度为常数级别

class Solution {
public:
    int numWays(int n) {
        if(n < 2) return 1;
        int a = 1, b = 2;
        int ans = 2;
        for(int i = 2; i < n; ++i){
            ans = (a + b)%1000000007;
            a = b;
            b = ans;
        }
        return ans;
    }
};