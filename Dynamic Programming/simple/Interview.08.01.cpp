// 动态规划
// 很简单，就是取模的求证费了点时间
// dp[i]为到第i级台阶共有多少种方法
static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int waysToStep(int n) {
        if(n < 3) return n;
        vector<int> dp(n+1, 0);
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 4;
        for(int i = 4; i <= n; ++i){
            dp[i] = ((dp[i-1] + dp[i-2])%1000000007 + dp[i-3])%1000000007;
        }
        return dp[n];
    }
};

// 简化版
// 用三个变量来保存前三级台阶的方法数即可
class Solution {
public:
    int waysToStep(int n) {
        if(n < 3) return n;
        vector<int> dp(n+1, 0);
        int a = 1, b = 2, c = 4;
        for(int i = 4; i <= n; ++i){
            int d = ((a + b)%1000000007 + c)%1000000007;
            a = b;
            b = c;
            c = d;
        }
        return c;
    }
};