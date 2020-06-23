static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 考察字母相关判断函数
// c++的几个内置函数
// islower(char c)   是否为小写字母
// isupper(char c)   是否为大写字母
// isdigit(char c)   是否为数字
// isalpha(char c)   是否为字母
// isalnum(char c)   是否为字母或者数字
// toupper(char c)   字母小转大
// tolower(char c)   字母大转小

class Solution {
public:
    bool isPalindrome(string s) {
        string tmp;
        for (auto c : s) {
            if (islower(c) || isdigit(c))  tmp += c;
            else if (isupper(c)) tmp += (c + 32);
        }
        int i = 0, j = tmp.size() - 1;
        while (i < j) {
            if (tmp[i] != tmp[j]) return false;
            i++;
            j--;
        }
        return true;
    }
};