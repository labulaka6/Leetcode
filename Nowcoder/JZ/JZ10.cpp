static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 动态规划
// 本题本质上和 JZ08. 跳台阶 一样，只是换了个问法
// 只有两种放法，竖着放一个或者横着放两个

class Solution {
public:
    int rectCover(int number) {
        if(number == 0) return 0;
        if(number == 2) return 1;
        int a = 1, b = 2;
        int ans = 2;
        for(int i = 2; i < number; ++i){
            ans = a + b;
            a = b;
            b = ans;
        }
        return ans;
    }
};