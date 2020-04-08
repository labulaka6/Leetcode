// 神仙解法 - 数学解法
// 先手必赢
// 可以控制拿偶数位置还是奇数位置，只要算出来哪个位置和最大即可
// 比如(0~9)十个位置
// 先手拿0对方只能拿1或者9，可以一直拿偶数位置
// 同理先手拿9对方只能拿0或者8，可以一直拿奇数位置

// 或者每次都选两头中较大的那一头，总共有偶数堆，先手必赢
// 直接return true即可

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        return ture;
    }
};

// 动态规划

class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        // 初始化 dp 数组
        vector<vector<pair<int, int>>> dp(n);
        // dp[i][j].first为剩下(i,j)时先手可以得到的最大分数
        // 同理dp[i][j].second为剩下(i,j)时后手可以得到的最大分数
        for(int i = 0; i < n; i++) {
            dp[i].resize(n);
        }
        // 初始化(0,0)用到的半边数组
        // 因为i<=j(或者说i>j的部分与i<j的部分是相反的,没必要再算一遍),所以正对角线左半部分用不到
        for (int i = 0; i < n; i++)
            for (int j = i; j < n; j++)
                dp[i][j] = make_pair(0, 0);
        // 填入 base case
        for (int i = 0; i < n; i++) {
            dp[i][i].first = piles[i];
            dp[i][i].second = 0;
        }
        // 斜着遍历数组
        for (int l = 2; l <= n; l++) {
            for (int i = 0; i <= n - l; i++) {
                int j = l + i - 1;
                // 先手选择最左边或最右边的分数
                // 在(i,j)范围内先手选择左边，相当于选了piles[i]然后在(i+1,j)范围内后手选择
                int left = piles[i] + dp[i+1][j].second;
                // 同理在(i,j)范围内先手选择右边，相当于选了piles[j]然后在(i,j-1)范围内后手选择
                int right = piles[j] + dp[i][j-1].second;
                // 套用状态转移方程
                if (left > right) {
                    dp[i][j].first = left;
                    // 在(i,j)范围内后手选择，如果别人选了左边，相当于在(i+1,j)范围内先手选择
                    dp[i][j].second = dp[i+1][j].first;
                } else {
                    dp[i][j].first = right;
                    // 在(i,j)范围内后手选择，如果别人选了右边，相当于在(i,j-1)范围内先手选择
                    dp[i][j].second = dp[i][j-1].first;
                }
            }
        }
        return dp[0][n-1].first > dp[0][n-1].second;
    }
};