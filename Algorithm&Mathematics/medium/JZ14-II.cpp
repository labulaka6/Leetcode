static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 贪心
// DP的缺陷
// 这个题和剪绳子I一样的描述，就是数据范围变大了。剪绳子可以用动态规划或者贪心做，这道题对于使用DP难度就增大了一些，
// 因为数据范围变得比较大时，long已经不足以去存储中间结果的状态，但是由于DP做法是枚举各种剪的情况然后取最大值，
// 因此只能通过使用BigInteger的方法去做。

// 那么这个题范围变大的本意是想让我们使用贪心算法能更好的求解
// (毕竟BigInteger使用起来麻烦，贪心没有数据溢出的问题，它是找当下的最优解，不需要比较，中间结果可以直接取模)。

// 全拆为3最优，2为次优
// 数学证明：https://leetcode-cn.com/problems/jian-sheng-zi-ii-lcof/solution/mian-shi-ti-14-ii-jian-sheng-zi-iitan-xin-er-fen-f/

class Solution {
public:
    int cuttingRope(int n) {
        if(n < 4) return n-1;
        long res = 1;
        while(n > 4) {
            res *= 3;
            res %= 1000000007;
            n -= 3;
        }
        return res * n % 1000000007;
    }
};

// 快速幂

class Solution {
public:
    int cuttingRope(int n) {
        if(n <= 3) return n - 1;
        int b = n % 3, p = 1000000007;
        long rem = 1, x = 3;
        for(int a = n / 3 - 1; a > 0; a /= 2) {
            if(a % 2 == 1) rem = (rem * x) % p;
            x = (x * x) % p;
        }
        if(b == 0) return rem * 3 % p;
        if(b == 1) return rem * 4 % p;
        return rem * 6 % p;
    }
};