// 动态规划

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        int len = min(m, n);
        bool dp[m][n][len];  // dp[i][j][k]代表右下角为(i,j)长度为k-1的区域是否全为1
        int count = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j][0] = (matrix[i][j] == 1);  // 长度为1只看本身即可
                count += dp[i][j][0] ? 1 : 0;
            }
        }
        for (int i = 1; i < m; i++) {  // 长度大于1
            for (int j = 1; j < n; j++) {
                for (int k = 1; k < len; k++) {
                    // 右下角为1，除去右下角的三个长度-1的正方形为全1的正方形
                    dp[i][j][k] = (matrix[i][j] == 1 && dp[i - 1][j][k - 1] && dp[i][j - 1][k - 1] && dp[i - 1][j - 1] [k - 1]);
                    if (dp[i][j][k]) {
                        count++;
                    }
                }
            }
        }
        return count;
    }

};

// dp数组可降一维
// 题目并不关心边长为1,2,...,k的各有多少个
// 以(i, j)为右下角边长为k的正方形全为1的话，那么以(i, j)为右下角边长分别为1,2,...,k - 1的正方形区域一定是全为1

class Solution {
public:
    int countSquares(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        int dp[m][n];  // dp[i][j]表示以(i,j)为右下角的正方形的最大边长，即以(i,j)为右下角的正方形有多少个
        memset(dp, 0, sizeof(dp));
        int ans = 0;
        // 预处理第一行和第一列
        for (int i = 0; i < m; i++) {
            ans += dp[i][0] = matrix[i][0];
        }
        for (int j = 0; j < n; j++) {
            ans += dp[0][j] = matrix[0][j];
        }
        // 上述过程(0, 0)判断了两次, 如果matrix[0][0] == 1，说明ans多算了一个
        if (matrix[0][0] == 1) {
            ans--;
        }
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == 1) {
                    dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
                    ans += dp[i][j];
                }
            }
        }
        return ans;
    }
};