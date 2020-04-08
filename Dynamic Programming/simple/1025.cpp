// 神仙解法：
// 数字N如果是奇数，它的约数必然都是奇数；若为偶数，则其约数可奇可偶。
// 无论N初始为多大的值，游戏最终只会进行到N=2时结束，那么谁轮到N=2时谁就会赢。
// 因为爱丽丝先手，N初始若为偶数，爱丽丝则只需一直选1，使鲍勃一直面临N为奇数的情况，这样爱丽丝稳赢；
// N初始若为奇数，那么爱丽丝第一次选完之后N必为偶数，那么鲍勃只需一直选1就会稳赢。
// 综述，判断N是奇数还是偶数，即可得出最终结果！

//下面这段函数的主要作用就是提高输入输出的速度，具体解释放在了印象笔记
static const auto _ = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    bool divisorGame(int N) {
        return N % 2 == 0;
    }
};
// 知道偶数先手必赢，使用N%2会随N的增大而增加计算量，而偶数的二进制最后一位为0，
// 奇数的最后一位为1，直接拿N与1进行与运算，时间和空间复杂度都是O（1）。
// 所以可以直接 return !(N&1);

// 动态规划解法：
// 1. 将所有的小于等于 N 的解都找出来，基于前面的，递推后面的。
// 2. 状态转移: 如果 i 的约数里面有存在为 False 的（即输掉的情况），则当前 i 应为 True；如果没有，则为 False。
static const auto _ = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    bool divisorGame(int N) {
        vector<bool> dp(N + 1, false);   // N+1是为了对齐，第N个是dp[N]，默认均为false
        for (int i = 2; i <= N; ++i)     // 从2开始
        {
            for (int j = 1; j <= (i / 2); ++j)  // 约数只需从1遍历到 i/2
            {
                if (i % j == 0 && dp[i - j] == false)  // j为i的约数且i-j(下一步)肯定输dp[i - j]==false，
                    dp[i] = true;                      // 则i肯定赢
                    break;
            }
        }                           //是一个递推关系，基于前面的，递推后面的
        return dp[N];
    }
};

