static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 位运算
// 单独看二进制某一位，先不看单独的那个数，其他所有数字都出现了 3 次，所以那一位是 1 的个数一定是 3 的倍数。
// 再考虑这个出现一次的数，如果这一位是 1 ，那么这一位 1 的次数模 3 为 1 ，否则的话模 3 就是 0 。
// 那么就很简单了，统计一下有多少个数这一位上是 1 ，然后模 3 取余数，结果就是这个单独的数这一位上的值了。
// 遍历 32 位整数的每一位，就可以得到这个单独的数是多少了。
// 推广到一般情况：
// 如果其他数都出现了 k 次，一个数出现了一次。那么如果 k 是偶数，还是把所有的数异或起来就行了。
// 如果 k 是奇数，那么统计每一位是 1 的个数，然后模 k 取余数就能得到那个单独的数了。

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i < 32; ++i) {
            int cnt = 0;
            for (auto x : nums) {
                cnt += (x>>i)&1;  // cnt统计当前第i位出现1的次数
            }
            res |= (cnt%3)<<i;  // 将对应位数的值(1或0)赋给res
        }
        return res;
    }
};

// 自动机
// https://leetcode-cn.com/problems/single-number-ii/solution/zi-dong-ji-wei-yun-suan-zui-xiang-xi-de-tui-dao-gu/

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int once = 0, twice = 0;
        for (auto x : nums) {
            once = (once^x)&(~twice);
            twice = (twice^x)&(~once);
        }
        return once;
    }
};