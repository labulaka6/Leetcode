static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 双指针

class Solution {
    // [i, j]是否构成回文字符串
    bool isPalindrome(string s, int i, int j) {
        while (i < j) {
            if (s[i++] != s[j--]) {
                return false;
            }
        }
        return true;
    }
public:
    bool validPalindrome(string s) {
        for(int i = 0, j = s.length() - 1; i < j ; ++i, --j){
            if(s[i] != s[j]){
                //分两种情况，一是右边减一，二是左边加一
                return isPalindrome(s, i, j-1) || isPalindrome(s, i+1, j);
            }
        }
        return true;
    }
};