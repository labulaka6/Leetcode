static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 切片函数

class Solution {
public:
    string reverseLeftWords(string s, int n) {
        int len = s.length();
        if(n > len) n = n % len;
        return s.substr(n, len - n) + s.substr(0, n);
    }
};

// 若规定不能使用切片函数

class Solution {
public:
    string reverseLeftWords(string s, int n) {
        int len = s.length();
        if(n > len) n = n % len;
        string ans = "";
        // for(int i = n; i < len; ++i){
        //     ans += s[i];
        // }
        // for(int i = 0; i < n; ++i){
        //     ans += s[i];
        // }
        // 利用求余运算简化代码
        for(int i = n; i < n + len; ++i){
            ans += s[i % len];
        }
        return ans;
    }
};