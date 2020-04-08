// 二维前缀和
static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int get(const vector<vector<int>>& pre, int m, int n, int x, int y) {  // 坐标约束
        x = max(min(x, m), 0);  // 约束坐标
        y = max(min(y, n), 0);  // 约束坐标
        return pre[x][y];
    }

    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int K) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> P(m + 1, vector<int>(n + 1));
        for (int i = 1; i <= m; ++i) {  // 得到一维前缀和数组
            for (int j = 1; j <= n; ++j) {
                // A[i-1][j-1] = P[i][j] - P[i - 1][j] - P[i][j - 1] + P[i - 1][j - 1]
                // 其中A[i][j]为数组本身(i,j)处的值，可将其看为1*1的矩阵
                // P[i][j]为以(i-1,j-1)为右下角的一维前缀和
                P[i][j] = P[i - 1][j] + P[i][j - 1] - P[i - 1][j - 1] + mat[i - 1][j - 1];
            }
        }

        vector<vector<int>> ans(m, vector<int>(n));
        for (int i = 0; i < m; ++i) {  // ans矩阵
            for (int j = 0; j < n; ++j) {
                ans[i][j] = get(P, m, n, i + K + 1, j + K + 1) - get(P, m, n, i - K, j + K + 1) - get(P, m, n, i + K + 1, j - K) + get(P, m, n, i - K, j - K);
            }
        }
        return ans;
    }
};