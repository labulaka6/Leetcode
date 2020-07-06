static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 数学分析
// 将 1 ~ n 的个位、十位、百位、...的 1 出现次数相加，即为 1 出现的总次数。
// 设数字 n 是个 x 位数，记 n 的第 i 位为 n[i]，则可将 n 写为 n[x]n[x-1]⋯n[2]n[1]:
// 称 " n[i] " 为 当前位 ，记为 cur ，
// 将 " n[i-1]n[i-2]⋯n[2]n[1] " 称为 低位 ，记为 low ；
// 将 " n[x]n[x-1]⋯n[i+2]n[i+1] " 称为 高位 ，记为 hig 。
// 将 10^i 称为 位因子 ，记为 digit 。

// 根据当前位 cur 值的不同，分为以下三种情况：
// 1. 当 cur = 0 时： 此位 1 的出现次数只由高位 high 决定，计算公式为：high × digit
// 2. 当 cur = 1 时： 此位 1 的出现次数由高位 high 和低位 low 决定，计算公式为：high × digit + low + 1
// 3. 当 cur = 2,3,⋯,9 时： 此位 1 的出现次数只由高位 high 决定，计算公式为：(high + 1) × digit


class Solution {
public:
    int countDigitOne(int n) {
        long digit = 1, res = 0;
        int high = n / 10, cur = n % 10, low = 0;
        while(high != 0 || cur != 0) {  // 当 high 和 cur 同时为 0 时，说明已经越过最高位，因此跳出
            if(cur == 0) res += high * digit;
            else if(cur == 1) res += high * digit + low + 1;
            else res += (high + 1) * digit;
            low += cur * digit;  // 将 cur 加入 low ，组成下轮 low
            cur = high % 10;  // 下轮 cur 是本轮 high 的最低位
            high /= 10;  // 将本轮 high 最低位删除，得到下轮 high
            digit *= 10;  // 位因子每轮 × 10
        }
        return res;
    }
};