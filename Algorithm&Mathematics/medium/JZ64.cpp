static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 直接使用等差数列求和公式，需要用到乘除法，排除
// 迭代计算，需要用到循环，排除
// 递归计算，终止条件需要用到判断，排除

// 所以利用逻辑运算符的短路效应
// 常见的逻辑运算符有三种，即 “与 && ”，“或 || ”，“非 ! ” ；而其有重要的短路效应，如下所示：
// if(A && B)  若 A 为 false ，则 B 的判断不会执行（即短路），直接判定 A && B 为 false
// if(A || B)  若 A 为 true ，则 B 的判断不会执行（即短路），直接判定 A || B 为 true
// 本题需要实现 “当 n = 1n=1 时终止递归” 的需求，可通过短路效应实现。
// n && n += sumNums(n - 1)  当 n = 0 时不成立 ，此时 “短路” ，终止后续递归

class Solution {
public:
    int sumNums(int n) {
        n && (n += sumNums(n-1));
        return n;
    }
};

// 还可使用快速乘来做