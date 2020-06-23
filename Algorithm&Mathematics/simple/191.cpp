static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 逐位计算

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int res = 0;
        while(n != 0){
            res += n&1;
            n = n >> 1;
        }
        return res;
    }
};

// 巧用 n & (n−1)
// (n−1) 解析： 二进制数字 n 最右边的 1 变成 0 ，此 1 右边的 0 都变成 1 。
// n&(n−1) 解析： 二进制数字 n 最右边的 1 变成 0 ，其余不变。
// 举例：
//       n = 10101000
//     n-1 = 10100111
// n&(n-1) = 10100000
// 消去左右边的1

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int res = 0;
        while(n != 0){
            n &= (n-1);
            res++;
        }
        return res;
    }
};