static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 动态规划
// dp[i][j] 为 s前i-1位是否与 p前j-1位匹配

class Solution {
public:
    bool isMatch(string s, string p) {
        s = " " + s;  // 防止该案例："\n" "c*"
        p = " " + p;
        int m = s.length(), n = p.length();
        bool dp[m+1][n+1];
        memset(dp, false, (m+1)*(n+1));
        dp[0][0] = true;
        for(int i = 1; i <= m; ++i){
            for(int j = 1; j <= n; ++j){
                // 字符相同或p为.
                if(s[i-1] == p[j-1] || p[j-1]=='.') dp[i][j] = dp[i-1][j-1];
                // p为*
                else if(p[j-1] == '*'){
                    // 必定无法匹配这个* p中*只能当作0个
                    if(s[i-1] != p[j-2] && p[j-2] != '.')
                        dp[i][j] = dp[i][j-2];
                    // 有可能可以匹配这个* p中*当作1 或者 p中*当作0 或者 s中多个字符匹配p中*
                    else{
                        dp[i][j] = dp[i][j-1] || dp[i][j-2] || dp[i-1][j];
                    }
                }
                // 其余情况不可能匹配上
            }
        }
        return dp[m][n];
    }
};

// 调库

class Solution {
public:
    bool isMatch(string s, string p) {
        return regex_match(s, regex(p));
    }
};