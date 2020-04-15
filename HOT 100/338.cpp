// 动态规划 - 找规律
// 奇数：二进制表示中，奇数一定比前面那个偶数多一个 1，因为多的就是最低位的 1。
// 举例： 0 = 0 , 1 = 1 , 2 = 10 , 3 = 11
// 偶数：二进制表示中，偶数中 1 的个数一定和除以 2 之后的那个数一样多。
// 因为最低位是 0，除以 2 就是右移一位，也就是把那个 0 抹掉而已，所以 1 的个数是不变的。
// 举例： 2 = 10 , 4 = 100 , 8 = 1000 3 = 11 , 6 = 110 , 12 = 1100
// 另外，0 的 1 个数为 0，于是就可以根据奇偶性开始遍历计算了。

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> result(num+1);
        result[0] = 0;
        for(int i = 1; i <= num; i++)
        {
            if(i % 2 == 1)
            {
                result[i] = result[i-1] + 1;
            }
            else
            {
                result[i] = result[i/2];
            }
        }
        return result;
    }
};

// 暴力解法

class Solution {
    int popcount(int x) {
        int count;
        for (count = 0; x != 0; ++count)
          x &= x - 1; //zeroing out the least significant nonzero bit
        return count;
    }
public:
    vector<int> countBits(int num) {
        vector<int> ans(num+1, 0);
        for (int i = 0; i <= num; ++i)
            ans[i] = popcount(i);
        return ans;
    }
};

// 动态规划 + 最后设置位
// 最后设置位是从右到左第一个为1的位。使用 x &= x - 1 将该位设置为0，就可以得到以下状态转移函数：
// P(x) = P(x & (x−1)) + 1;

class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> ans =(num+1, 0);
        for (int i = 1; i <= num; ++i)
            ans[i] = ans[i & (i - 1)] + 1;
        return ans;
  }
}；。