static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 动态规划
// f(n) = f(n-1) + f(n-2)
// 初始状态f(0) = 0, f(1) = 1
// f(n) 只与 f(n-1) 和 f(n-2) 有关
// 可优化空间复杂度至常数级别

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