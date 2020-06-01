static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 异或
// 将 5 个元音字母出现次数的奇偶视为一种状态，一共有 32 种状态，不妨使用一个整数代表状态，
// 第 0 位为 1 表示 a 出现奇数次，第一位为 1 表示 e 出现奇数次……以此类推。仅有状态 0 符合题意。
// 而如果子串 [0，i] 与字串 [0,j] 状态相同，那么字串 [i+1,j] 的状态一定是 0，
// 因此可以记录每个状态第一次出现的位置，此后再出现该状态时相减即可。
// 需要注意状态 0 首次出现的位置应该设定为 -1。
// 在计算状态的时候可以利用异或运算。

// 1、cur 记录了遍历到当前下标 i 的 a、e、i、o、u 的情况，是一个前缀和的概念，并且是「异或前缀和」；
// 把前缀异或和的信息表示在一个二进制只有 5 位的整数 cur 里，方便以后查找；
// 2、定义成「异或前缀和」是因为中间遍历的那些元音字符相同的，在异或运算下都抵消了，这是符合题目的要求的：「中间遍历的那些字符出现偶数次元音字符」；
// 重点：子串中 a、e、i、o、u 只出现偶数次，等价于：在这个子串里异或和为 0；
// 3、由于要记录「最长的」符合要求的子串的长度，于是只需要记录第一次出现的「前缀异或和」，以后再次出现的相同的「异或前缀和」的时候，将下标相减（注意考虑边界情况）。
// 因此把所有的「前缀异或和」信息保存在一个哈希表里，由于这里所有的前缀异或和状态有限（2^5 = 32），用数组或者哈希表均可。

// 这个哈希表的 key 是前缀异或和对应的整数 cur， value 是当前遍历到的下标，初始化的时候赋值为一个特殊值，表示当前的前缀异或和没有出现。

class Solution {
public:
    int findTheLongestSubstring(string s) {
        vector<int> pre(32, INT_MAX);
        pre[0] = -1;
        const int N = s.size();
        int cur = 0;
        int ans = 0;
        for(int i = 0; i < N; ++i){
            switch(s[i]){
                case 'a':
                    cur ^= 1;
                    break;
                case 'e':
                    cur ^= 2;
                    break;
                case 'i':
                    cur ^= 4;
                    break;
                case 'o':
                    cur ^= 8;
                    break;
                case 'u':
                    cur ^= 16;
                    break;
                default:
                    break;
            }
            if(pre[cur] == INT_MAX) pre[cur] = i;
            else ans = max(ans, i - pre[cur]);
        }
        return ans;
    }
};