// 动态规划
// dp[i][j]为到(i,j)位置时有多少种不同路径
// 如果dp[i][j]为障碍物，则直接置为0
// 否则dp[i][j] = dp[i-1][j] + dp[i][j-1];

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        long dp[m][n];
        memset(dp, 0, sizeof(dp));
        for(int i = 0; i < m; ++i){    // 初始化第一列
            if(obstacleGrid[i][0] == 0){  // 不是障碍物
                dp[i][0] = 1;
            }else{   // 障碍物则后边的全是0
                break;
            }
        }
        for(int j = 0; j < n; ++j){    // 初始化第一列
            if(obstacleGrid[0][j] == 0){
                dp[0][j] = 1;
            }else{
                break;
            }
        }
        for(int i = 1; i < m; ++i){
            for(int j = 1; j < n; ++j){
                if(obstacleGrid[i][j] == 0){  // 不是障碍物
                    dp[i][j] = dp[i-1][j] + dp[i][j-1];
                }else{  // 遇到障碍物置0
                    dp[i][j] = 0;
                }
            }
        }
        return dp[m-1][n-1];
    }
};