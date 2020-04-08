// 哈希表
// 回文字符串，如果字符n是双数个可以全部用，
// 若果是奇数个，则可以用n-1个(开始没有想到这种情况，只计算了所有偶数和+1)
// 则每个字符可以利用的数量为 n/2 *2
// 然后再加随便一个中心(如果有字符的数量是奇数个的话)

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int longestPalindrome(string s) {
        unordered_map<char, int> count;
        int ans = 0;
        for (char c : s)
            ++count[c];
        bool flag = false;  // 是否有字符数为奇数
        for (auto p : count) {
            int v = p.second;
            ans += v / 2 * 2;
            if (v % 2 == 1) flag = true;
        }
        if(flag) ans++;
        return ans;
    }
};