// 动态规划
// dp[i]为i存在的二叉排序树的个数
// 若以1为根节点，则没有左子树，右子树有i-1个结点
// 若以2为根节点，则左子树有1个结点，右子树有i-2个结点
// 以此类推
// i存在的二叉排序树的个数 即为 从1到i为根结点的情况相加
// dp[i] = dp[i-1] + dp[1]dp[i-2] + ... + dp[i-2]dp[1] + dp[i-1]
static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int numTrees(int n) {
        vector<int> dp(n+1, 0);
        dp[0] = 1;  // 为了构造递推式(包含乘法),dp[0]初始化为1
        dp[1] = 1;
        for(int i = 2; i < n + 1; ++i){
            for(int j = 0; j < i; ++j){
                dp[i] += dp[j]*dp[i-1-j];
            }
        }
        return dp[n];
    }
};

// 用卡塔兰数求解
class Solution {
public:
    int numTrees(int n) {
    long C = 1;
    for (int i = 0; i < n; ++i) {
      C = C * 2 * (2 * i + 1) / (i + 2);
    }
    return (int)C;
  }
};