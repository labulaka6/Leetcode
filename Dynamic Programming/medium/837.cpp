static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 动态规划

class Solution {
public:
    double new21Game(int N, int K, int W) {
        if (K == 0) return 1.0;
        vector<double> dp(K + W, 0.0);
        double s = 0;
        for (int i = K; i < K + W; ++i) {
            if(i <= N) dp[i] = 1.0;
            s += dp[i];
        }
        for (int i = K - 1; i >= 0; --i) {
            dp[i] = s / W;
            s = s - dp[i + W] + dp[i];
        }
        // 或者这样也可以
        // dp[K - 1] = 1.0 * min(N - K + 1, W) / W;
        // for (int i = K - 2; i >= 0; i--) {
        //     dp[i] = dp[i + 1] - (dp[i + W + 1] - dp[i + 1]) / W;
        // }
        return dp[0];
    }
};