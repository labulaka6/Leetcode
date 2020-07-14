static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 动态规划
// 从右下往左上进行动态规划。令 dp[i][j] 表示从坐标 (i,j) 到终点所需的最小初始值。
// 换句话说，当到达坐标 (i,j) 时，如果此时路径和不小于 dp[i][j]，就能到达终点。

class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int n = dungeon.size(), m = dungeon[0].size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, INT_MAX));
        dp[n][m - 1] = dp[n - 1][m] = 1;
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                int minn = min(dp[i + 1][j], dp[i][j + 1]);
                dp[i][j] = max(minn - dungeon[i][j], 1);
            }
        }
        return dp[0][0];
    }
};