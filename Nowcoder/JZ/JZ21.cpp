static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 模拟栈的运行
// 按照压栈序列的顺序执行。每次入栈后，循环判断 “栈顶元素 == 弹出序列的当前元素” 是否成立，将符合弹出序列顺序的栈顶元素全部弹出。
// 如果出栈序列是入栈序列的一个出栈序列，则运行完后栈为空

class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> s;
        int i = 0;
        for(int num : pushed) {
            s.push(num); // num 入栈
            while(!s.empty() && s.top() == popped[i]) { // 循环判断与出栈
                s.pop();
                i++;
            }
        }
        return s.empty();
    }
};