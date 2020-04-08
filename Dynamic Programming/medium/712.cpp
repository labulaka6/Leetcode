// 动态规划

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int minimumDeleteSum(string s1, string s2) {
        int m = s1.length();
        int n = s2.length();
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));  // s1的前i个字符与s2的前j个字符的最小ASCII删除和
        for(int i = 1; i <= m; ++i){
            dp[i][0] = dp[i-1][0] + (int)s1[i-1];
        }
        for(int j = 1; j <= n; ++j){
            dp[0][j] = dp[0][j-1] + (int)s2[j-1];
        }
        // 1.s1[i-1] == s2[j-1]，新增的两个字符相等的情况下，没有必要删除之前的结果，因此dp[i][j] = dp[i-1][j-1]
        // 2.s1[i-1] != s2[j-1]，取两者的最小值
        // （1）保留s2串，删除s1串的字符，dp[i][j] = dp[i-1][j] + s1.charAt(i-1)
        // （2）保留s1串，删除s2串的字符，dp[i][j] = dp[i][j-1] + s2.charAt(j-1)
        for(int i = 1; i <= m; ++i){
            for(int j = 1; j <= n; ++j){
                int tem1 = s1[i-1], tem2 = s2[j-1];
                if(tem1 == tem2){
                    dp[i][j] = dp[i-1][j-1];
                }else{
                    dp[i][j] = min(dp[i-1][j] + tem1, dp[i][j-1] + tem2);
                }
            }
        }
        return dp[m][n];
    }
};