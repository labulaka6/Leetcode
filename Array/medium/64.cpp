// 动态规划
// dp[i][j]表示到(i,j)的最短路径

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        if(m == 0) return 0;
        int n = grid[0].size();
        if(n == 0) return 0;
        int dp[m][n];
        memset(dp, 0, sizeof(dp));
        dp[0][0] = grid[0][0];
        for(int i = 1; i < m; ++i){  // 初始化第一列
            dp[i][0] += dp[i-1][0] + grid[i][0];
        }
        for(int j = 1; j < n; ++j){  // 初始化第一行
            dp[0][j] += dp[0][j-1] + grid[0][j];
        }
        for(int i = 1; i < m; ++i){
            for(int j = 1; j < n; ++j){
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
            }
        }
        return dp[m-1][n-1];
    }
};

// 也可在原数组完成计算，不需要新申请数组
// 很简单，这里不再详述

// 一维数组动态规划
// 可以用一个一维数组来代替二维数组，dp数组的大小和行大小相同。
// 这是因为对于某个固定状态，只需要考虑下方和右侧的节点。
// 首先初始化dp数组最后一个元素也就是是右下角的元素值，然后向左移更新每个 dp(j)为：
// dp(j) = grid(i, j) + min(dp(j), dp(j+1))
// 对于每一行都重复这个过程，然后向上一行移动，计算完成后 dp(0)就是最后的结果。
// 相当于从后往前推，同理也可以从前往后推

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
       int dp[grid[0].size()];
       memset(dp, 0, sizeof(dp));
       for (int i = grid.size() - 1; i >= 0; i--) {
           for (int j = grid[0].size() - 1; j >= 0; j--) {
               if(i == grid.size() - 1 && j != grid[0].size() - 1)  // 在最后一行但不在最后一列
                   dp[j] = grid[i][j] +  dp[j + 1];
               else if(j == grid[0].size() - 1 && i != grid.size() - 1)  // 在最后一列但不在最后一行
                   dp[j] = grid[i][j] + dp[j];
               else if(j != grid[0].size() - 1 && i != grid.size() - 1)  // 既不在最后一行也不在最后一列
                   dp[j] = grid[i][j] + min(dp[j], dp[j + 1]);
               else  // 在最后一个位置(最后一行，最后一列)
                   dp[j] = grid[i][j];
           }
       }
       return dp[0];
   }
};