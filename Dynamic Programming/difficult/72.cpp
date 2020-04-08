// 动态规划

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.length();
        int m = word2.length();

        // 有一个字符串为空串
        if (n * m == 0) return n + m;

        // DP 数组
        int D[n + 1][m + 1];

        // 边界状态初始化
        for (int i = 0; i < n + 1; i++) {
            D[i][0] = i;
        }
        for (int j = 0; j < m + 1; j++) {
            D[0][j] = j;
        }

        // 计算所有 DP 值
        for (int i = 1; i < n + 1; i++) {
            for (int j = 1; j < m + 1; j++) {
                int left = D[i - 1][j] + 1;  // 删除word1[i]字符
                int down = D[i][j - 1] + 1;  // 在word1[i]插入一个word2[j]字符
                int left_down = D[i - 1][j - 1];  // word1[i]与word2[j]相同
                if (word1[i - 1] != word2[j - 1]) left_down += 1;  // word1[i]与word2[j]不同
                D[i][j] = min(left, min(down, left_down));

            }
        }
        return D[n][m];
    }
};