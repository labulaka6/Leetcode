static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 去重：一开始只考虑有1分的硬币 然后在循环中考虑再加入5分的硬币，此时仅有1分 5分
// 再考虑加入10分，此时仅有1分 5分 10分 以此类推
// 每一个循环中，如果有变化，则是新加入的种类的硬币的数量发生了变化，才有计数变化，
// 即每次硬币的变化都不同，数量情况唯一
// 拿10打比方，初始化后dp[5]=dp[10]=1，即表示全由1组成，
// 第一次循环，dp[5]=dp[5]+dp[0]=2，即为1+1+1+1+1和5+0组成，
// dp[10]=dp[10]+dp[5]=1+2=3，即为在全由1组成的基础上，加上了5+1+1+1+1+1和5+5，
// 第二次循环，dp[5]不变，dp[10]=dp[10]+dp[0]=3+1=4,即表示在上一次循环的基础上加上了10+0。

class Solution {
private:
    static constexpr int mod = 1000000007;
    static constexpr int coins[4] = {25, 10, 5, 1};

public:
    int waysToChange(int n) {
        vector<int> f(n + 1);
        f[0] = 1;
        for (int c = 0; c < 4; ++c) {
            int coin = coins[c];
            for (int i = coin; i <= n; ++i) {
                f[i] = (f[i] + f[i - coin]) % mod;
            }
        }
        return f[n];
    }
};