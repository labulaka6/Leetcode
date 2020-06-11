static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int fib(int n) {
        if(n == 0) return 0;
        if(n == 1) return 1;
        int a = 1, b = 1;
        int ans = 1;
        for(int i = 2; i < n; ++i){  // 从第三项开始
            ans = (a + b)%1000000007;
            a = b;
            b = ans;
        }
        return ans;
    }
};