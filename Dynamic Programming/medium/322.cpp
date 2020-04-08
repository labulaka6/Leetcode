// 动态规划

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount+1, amount+1);  // dp[i]为amount为i时需要的最小硬币数
        // dp数组初始化为amount + 1 ，因为凑成amount金额的硬币数最多只可能等于amount(全用 1 元面值的硬币)
        // 所以初始化为 amount + 1 就相当于初始化为正无穷，便于后续取最小值。
        dp[0] = 0;  // 占位，没有用到
        for(int i = 0; i < dp.size(); ++i){  // 求解所有小于amount的dp[i]
            for(int coin : coins){    // 遍历所有硬币
                if(i - coin < 0) continue;  // 子问题无解，跳过
                dp[i] = min(dp[i], dp[i-coin] + 1);  // 状态转移方程,dp[i]就是dp[i - coin]+1中最小的一个
            }// 比如我有1,2,5面值的硬币 我
        }    //要凑15,我用凑14(15-1)最少的硬币数+面值1的硬币即为基于14这种情况大的最少硬币数
             // 同理也可以用凑13(15-2)+面值2的硬币即为基于13这种情况大的最少硬币数,以此类推10+面值5,
             // 然后三种情况取最小即凑15的最小硬币数
             // 注意这里凑15无论怎么凑只可能有这三种情况,即已完成穷举
        return (dp[amount] == amount + 1) ? -1 : dp[amount];  // 不能拼凑的情况
    }
};
