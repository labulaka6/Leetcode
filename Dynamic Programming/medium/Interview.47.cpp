// 动态规划
// 为了方便计算(边界问题不用单独考虑),dp[i][j]表示到(i-1,j-1)位置时的最大价值

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int maxValue(vector<vector<int>>& grid) {
        int m = grid.size();
        if(m == 0) return 0;
        int n = grid[0].size();
        if(n == 0) return 0;
        int dp[m+1][n+1];
        memset(dp,0,sizeof(dp));
        for(int i = 1; i < m + 1; ++i){
            for(int j = 1; j < n + 1; ++j){
                // 只能从上边或者左边来到(i-1, j-1)
                dp[i][j] = max(dp[i-1][j] + grid[i-1][j-1], dp[i][j-1] + grid[i-1][j-1]);
            }
        }
        return dp[m][n];
    }
};

// 改版
// 只需要在原数组上修改即可
class Solution {
public:
    int maxValue(vector<vector<int>>& grid) {
        int m = grid.size();
        if(m == 0) return 0;
        int n = grid[0].size();
        if(n == 0) return 0;
        for(int i = 1; i < m; ++i){
            grid[i][0] += grid[i-1][0];
        }
        for(int j = 1; j < n; ++j){
            grid[0][j] += grid[0][j-1];
        }
        for(int i = 1; i < m; ++i){
            for(int j = 1; j < n; ++j){
                // 只能从上边或者左边来到(i, j)
                grid[i][j] = max(grid[i-1][j] + grid[i][j], grid[i][j-1] + grid[i][j]);
            }
        }
        return grid[m-1][n-1];
    }
};

