// 动态规划
// 如果第一个人坐到自己的座位上，那么后面所有人都会坐到自己座位上
// 如果第一个人坐到第n个人的座位上，第n个人没有可能坐到自己座位上
// 如果第一个人坐到除了自己和第n个人之外的任何座位上，则情况与n-1个座位相同
// 则状态转移方程为 dp[i] = 1/i + ((i-2)/i)*dp[i-1]

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    double nthPersonGetsNthSeat(int n) {
        double dp[n+1];
        dp[1] = 1;
        for(int m = 2; m <= n; ++m) {
            double i = m;
            dp[m] = (1 / i) + (dp[m - 1] * (i - 2) / i);
        }
        return dp[n];
    }
};

// 数学法
// 无论n为多少，只要n>=3就可以简化为n=3

class Solution {
public:
    double nthPersonGetsNthSeat(int n) {
        if(n == 1) return 1;
        else return 0.5;
    }
};
