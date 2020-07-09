static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 其实就是用位运算实现加法：
// 普通加法中：例如 13 + 8
// 如果先将对应位子的数字相加，不考虑进位的话，应该是
// 3 + 8 = 1 进位为1
// 1 + 0 = 1 进位为0
// 之后将个位的进位1 与十位上的1相加
// 1 + 1 = 2 进位为0
// 如果我们将此方法带入到二进制的运算中是否可行呢？
// 13 => 1101
// 8 => 1000
// 首先不考虑进位将两个二进制相加 1101 + 1000 = 0101 这个操作与(1101 异或 1000)的出来的值相同
// 从上一步中可以得出，进位为1，且在第3位（从右往左数）进1位 => 1000 << 1 = 10000
// 之后将 10000 + 0101 = 10101 => 21 此时进位位0，即可退出。

// 迭代

class Solution {
public:
    int add(int a, int b) {
        while(b != 0) { // 当进位为 0 时跳出
            int c = (unsigned int) (a & b) << 1;  // c = 进位
            a ^= b; // a = 非进位和
            b = c; // b = 进位
        }
        return a;
    }
};

// 递归

class Solution {
public:
    int add(int a, int b) {
        return b ? add(a^b, (unsigned int)(a&b)<<1) : a;
    }
};