// 动态规划
// dp[i][j]为到(i,j)位置时有多少种不同路径
// dp[i][j] = dp[i-1][j] + dp[i][j-1];

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int uniquePaths(int m, int n) {
        int dp[m][n];
        memset(dp, 0, sizeof(dp));
        for(int i = 0; i < m; ++i){  // 初始化第一列
            dp[i][0] = 1;
        }
        for(int j = 0; j < n; ++j){  // 初始化第一行
            dp[0][j] = 1;
        }
        for(int i = 1; i < m; ++i){
            for(int j = 1; j < n; ++j){
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};

// 数学法
// 题目主要是排列组合，机器人总共需要向下走m-1步，向右n-1步，
// 转化为数学问题就是在m+n-2个空格中寻找m-1个向下走，次数就是求C(m+n-2)(m-1)的结果。
// 接下来的问题，就是如何求。
// 如果直接求(m+n-2)!的结果，很容易超出int限制，所以使用double来储存，最后再将其转化为int输出。

class Solution {
public:
    int uniquePaths(int m, int n) {
        double num=1;
        for(int i=1;i<m;i++){
            num *= (i+n-1);
            num /= i;
        }
        int ans=int(num);
        return(ans);
    }
};
