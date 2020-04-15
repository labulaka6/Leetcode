// 位运算

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int hammingDistance(int x, int y) {
        int count = 0;
        int tem = x^y;  // 异或后，不同的位留下的都是1
        while(tem > 0)
        {
            if(tem & 1 == 1)  // 把所有的1数出来，用与的方法
            {
                count++;
            }
            tem >>= 1;  // 算术右移一位
        }
        return count;
    }
};

// 优化
// 将循环次数变为1的个数

class Solution {
public:
    int hammingDistance(int x, int y) {
        int count = 0;
        int tem = x^y;  // 异或后，不同的位留下的都是1
        while(tem)
        {
            count++;
            tem &= tem - 1;  // 将循环次数变为1的个数
        }
        return count;
    }
};