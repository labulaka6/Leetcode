// 原始解法 - 动态规划
// 超出时间限制

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
    int count(int K, int N, vector<vector<int>>& dp){
        if(K == 1) return N;
        if(N == 0) return 0;
        // 避免重复计算
        if(dp[K][N] != 0) return dp[K][N];

        int res = INT_MAX;
        // 穷举所有可能的选择
        for(int i = 1; i <= N; ++i){
            // 在第i层丢鸡蛋,碎了证明在下边K-1,i-1,没碎证明在上边K,N-i
            res = min(res, max(count(K, N-i, dp), count(K-1, i-1, dp)) + 1);
        }
        // 记入备忘录
        dp[K][N] = res;
        return res;
    }
public:
    int superEggDrop(int K, int N) {
        vector<vector<int>> dp(K+1, vector<int> (N+1, 0));
        return count(K, N, dp);
    }
};

// 优化
// 动态规划 + 二分查找

class Solution {
    int count(int K, int N, vector<vector<int>>& dp){
        if(K == 1) return N;
        if(N == 0) return 0;
        // 避免重复计算
        if(dp[K][N] != 0) return dp[K][N];

        int res = INT_MAX;
        // 用二分搜索代替线性搜索
        int lo= 1, hi = N;
        while(lo <= hi){
            int mid = (lo + hi)/2;
            int broken = count(K - 1, mid - 1, dp); // 碎
            int not_broken = count(K, N - mid, dp); // 没碎
            // res = min(max(碎，没碎) + 1)
            if(broken > not_broken){
                hi = mid - 1;
                res = min(res, broken + 1);
            }else{
                lo = mid + 1;
                res = min(res, not_broken + 1);
            }
        }
        // 记入备忘录
        dp[K][N] = res;
        return res;
    }
public:
    int superEggDrop(int K, int N) {
        vector<vector<int>> dp(K+1, vector<int> (N+1, 0));
        return count(K, N, dp);
    }
};

// 另一种动态规划
// dp[k][m] = n
// 当前有 k 个鸡蛋，可以尝试扔 m 次鸡蛋
// 这个状态下，最坏情况下最多能确切测试一栋 n 层的楼

// 比如说 dp[1][7] = 7 表示：
// 现在有 1 个鸡蛋，允许你扔 7 次;
// 这个状态下最多给你 7 层楼，
// 使得你可以确定楼层 F 使得鸡蛋恰好摔不碎
//（一层一层线性探查）

class Solution {
public:
    int superEggDrop(int K, int N) {
        // m 最多不会超过 N 次（线性扫描）
        vector<vector<int>> dp(K+1, vector<int> (N+1, 0));
        // base case:
        // dp[0][..] = 0
        // dp[..][0] = 0
        // 初始化后的数组都为 0
        int m = 0;
        while (dp[K][m] < N) {
            m++;
            for (int k = 1; k <= K; k++)
                dp[k][m] = dp[k][m - 1] + dp[k - 1][m - 1] + 1;
        }
        // 等价于
        // for (int m = 1; dp[K][m] < N; m++)
        //     for (int k = 1; k <= K; k++)
        //         dp[k][m] = dp[k][m - 1] + dp[k - 1][m - 1] + 1;
        return m;
    }
};