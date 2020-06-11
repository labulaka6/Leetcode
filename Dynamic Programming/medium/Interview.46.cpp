static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 动态规划
// dp[i]为从左边第0位起到第i位的翻译方法数
// 若第i位与第i-1位构成一种翻译(即在10~25之间)，则dp[i] = dp[i-1] + dp[i-2]
// 若不构成，则dp[i] = dp[i-1]
// 可以看出 dp[i] 只与 dp[i-1] 和 dp[i-2] 有关，可以优化，只用两个变量来记录前两位即可

class Solution {
public:
    int translateNum(int num) {
        string s = to_string(num);
        int a = 1, b = 1;
        for(int i = 2; i <= s.length(); ++i) {
            auto tmp = s.substr(i - 2, 2);
            int c = (tmp >= "10" && tmp <="25") ? a + b : a;
            b = a;
            a = c;
        }
        return a;
    }
};

// 递归
// 这道题其实就是一个递归：
// 递归出口是num是只有一位数，以xyzcba为例，先取最后两位（个位和十位）即ba，
// 如果 ba>25 或 ba < 10，必然不能分解成 f(xyzcb) + f(xyzc)，此时只能分解成 f(xyzcb)

class Solution {
public:
    int translateNum(int num) {
        if (num < 10) return 1;
        return (num%100 < 10 || num%100 > 25) ? translateNum(num/10) : translateNum(num/10) + translateNum(num/100);
    }
};