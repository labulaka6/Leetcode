static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 暴力法 - 穷举每一种可能
// 超出时间限制  26 / 50 个通过测试用例

// 对于给定的数 n，F(n) 表示将 n 分解成多个(≥2)整数的最大乘积，那么有以下几种情况：
// 1. 将n分解成两个数:
// F(n) = i∗(n−i), (i=1,2,...,n−1)
// 2️. 将n分解成两个以上的数:
// 也就是说要对 i 和 n - i 进一步分解，那么就有三种情况（继续分解其中一个或两个都继续分解），
// 将i和n - i进一步分解的最大乘积分别记为 F(i)和F(n−i)，那么有：
//            / i∗F(n−i)        对 n−i 继续分解
// F(n) = max | F(i)∗(n−i)      对 i 继续分解
//            \ F(i)∗F(n−i)     对 i和 n−i 都继续分解
// 但是，观察上面的表达式，不难发现，当i取遍[1,n−1]时，由于i和n - i的取值对称，
// i∗F(n−i) 和 F(i)∗(n−i)的取值集合是一样的，也就是说这两种情况算出来的结果是一样的，
// 所以只取其中一种就可以了。对于F(i)*F(n-i)，其实这种情况也是不用考虑的，
// 因为 i∗(n−i)和i∗F(n−i)已经包含了所有的分解情况了。那么整个表达式就为：
// F(n) = max{i∗(n−i), i∗F(n−i)}, (i=1,2,...,n−1)

class Solution {
public:
    int integerBreak(int n) {
        if (n == 2) return 1;
        int res = -1;
        for (int i = 1; i <= n - 1; ++i) {
            res = max(res, max(i * (n - i), i * integerBreak(n - i)));
        }
        return res;
    }
};

// 记忆化递归(备忘录)
// 自上而下
// 对于暴力搜索，不难得出该方法的时间复杂度为指数级别，显然不能满足题目要求。那么如此耗时的原因也是因为在递归的过程中计算了很多重复值。
// 例如，F(n-2)和F(n-3)至少重复计算了两次，并且在后面会有更多次重复运算，而这部分重复运算完全是没有必要的，
// 如果每次求完一个F(i)，都将其保存起来，下次再求的时候直接读取保存的值就行了，这显然会节省大量时间。
// 只要用一个数组存放每次的F(i)，记为memory，这个数组一般称之为备忘录数组。

class Solution {
private:
    int integerBreakHelper(int n, vector<int>& memory) {
        if (n == 2) return 1;
        // memory的初始值为0，如果它不为0，说明已经计算过了，直接返回即可
        if (memory[n] != 0) return memory[n];
        int res = -1;
        for (int i = 1; i <= n - 1; ++i) {
            res = max(res, max(i * integerBreakHelper(n - i, memory), i * (n - i)));
        }
        // 将每次计算的结果保存到备忘录数组中
        memory[n] = res;
        return res;
    }

public:
    int integerBreak(int n) {
        vector<int> memory(n + 1, 0);
        return integerBreakHelper(n, memory);
    }
};

// 动态规划
// 自下而上
// 将记忆化递归转换为递推关系

class Solution {
public:
    int integerBreak(int n) {
        vector<int> dp(n+1, 0);
        dp[2] = 1;
        for(int i = 3; i <= n; ++i){
            for(int j = 1; j < i; ++j){
                dp[i] = max(dp[i], max(j*dp[i-j], j*(i-j)));
            }
        }
        return dp[n];
    }
};