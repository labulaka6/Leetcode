static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 二维dp
// 若某格子值为 1 ，则以此为右下角的正方形的、最大边长为：
// 上面的正方形、左面的正方形或左上的正方形中，最小的那个，再加上此格。
// 即为 min(上, 左, 左上) + 1

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.size() < 1 || matrix[0].size() < 1) return 0;

        int height = matrix.size();
        int width = matrix[0].size();
        int maxSide = 0;

        // 相当于已经预处理新增第一行、第一列均为0
        vector<vector<int>> dp(height+1, vector<int> (width+1, 0));

        for (int row = 0; row < height; ++row) {
            for (int col = 0; col < width; ++col) {
                if (matrix[row][col] == '1') {
                    dp[row + 1][col + 1] = min(min(dp[row + 1][col], dp[row][col + 1]), dp[row][col]) + 1;
                    maxSide = max(maxSide, dp[row + 1][col + 1]);
                }
            }
        }
        return maxSide * maxSide;
    }
};

// 优化为一维dp

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.size() < 1 || matrix[0].size() < 1) return 0;

        int height = matrix.size();
        int width = matrix[0].size();
        int maxSide = 0;

        // 相当于已经预处理新增第一行、第一列均为0
        //  vector<vector<int>> dp(height+1, vector<int> (width+1, 0));
        vector<int> dp(width+1, 0);
        int northwest = 0; // 西北角、左上角

        //  for (int row = 0; row < height; row) {
        for (auto chars : matrix) {
            northwest = 0; // 遍历每行时，还原回辅助的原值0
            for (int col = 0; col < width; col++) {
                int nextNorthwest = dp[col + 1];
                if (chars[col] == '1') {
                    // dp[row + 1][col + 1] = min(min(dp[row + 1][col], dp[row][col + 1]), dp[row][col]) + 1;
                    dp[col + 1] = min(min(dp[col], dp[col + 1]), northwest) + 1;

                    // maxSide = max(maxSide, dp[row + 1][col + 1]);
                    maxSide = max(maxSide, dp[col + 1]);
                } else {
                    dp[col + 1] = 0;
                }
                northwest = nextNorthwest;
            }
        }
        return maxSide * maxSide;
    }
};