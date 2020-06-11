static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 翻转

class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0) return false;
        long tmp = x;
        long n = 0;
        while(tmp > 0){
            n = 10*n + tmp%10;
            tmp /= 10;
        }
        return n == x;
    }
};

// 优化
// 翻转一半即可

class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0 || (x % 10 == 0 && x != 0)) return false;
        int revertedNumber = 0;
        while (x > revertedNumber) {
            revertedNumber = revertedNumber * 10 + x % 10;
            x /= 10;
        }
        return x == revertedNumber || x == revertedNumber / 10;
    }
};