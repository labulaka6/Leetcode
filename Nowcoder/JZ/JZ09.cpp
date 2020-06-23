// 一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。
// 求该青蛙跳上一个n级的台阶总共有多少种跳法。

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 动态规划
// dp[i] 为i阶台阶共有多少种跳法
// 初始状态dp[0] = 1, dp[1] = 1
// dp[i] = dp[i-1] + dp[i-2] + ... + dp[1] + dp[0],即前面所有项累加
// 可优化空间复杂度为常数级别

class Solution {
public:
    int jumpFloorII(int number) {
        if(number < 2) return 1;
        int ans = 2;
        for(int i = 2; i < number; ++i){
            ans += ans;
        }
        return ans;
    }
};

// 稍微留意即可注意到其实 当number >= 2时，ans = 2^(number-1)
// 或者 从number = 1开始，ans为首项为1，比值为2的等比数列前number项和问题