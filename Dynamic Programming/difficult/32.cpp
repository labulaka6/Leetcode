static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 暴力法
// 超出时间限制 219 / 230 个通过测试用例

class Solution {
    bool valid(string& s, int l, int r){
        if((r - l + 1)%2 != 0) return false;
        if(s[l] == ')') return false;
        stack<int> st;
        for(int i = l; i <= r; ++i){
            if(s[i] == '(') st.push(1);
            else if(!st.empty()) st.pop();
            else return false;
        }
        return st.empty();
    }

public:
    int longestValidParentheses(string s) {
        if(s.length() < 2) return 0;
        int ans = 0;
        for(int i = 0; i < s.length()-1; ++i){
            for(int j = i + 1; j < s.length(); ++j){
                if(valid(s, i, j)) ans = max(ans, j - i + 1);
            }
        }
        return ans;
    }
};

// 栈

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.length();
        if(n < 2) return 0;
        stack<int> st;
        st.push(-1);
        int ans = 0;
        for(int i = 0; i < n; ++i){
            if(s[i] == '(') st.push(i);
            else{
                st.pop();  // 先出栈，可以保证可栈顶元素为可匹配括号中第一个左括号(的前一个位置
                if(st.empty()) st.push(i);
                else ans = max(ans, i - st.top());  // 这样 i - st.top() 即为可匹配括号的长度
            }
        }
        return ans;
    }
};

// 动态规划
// dp[i]为以i为结尾的最长有效括号的长度

class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.length();
        if(n < 2) return 0;
        vector<int> dp(n, 0);
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (i > 0 && s[i] == ')') {
                if (s[i-1] == '(') {
                    dp[i] = (i - 2 >= 0 ? dp[i - 2] + 2 : 2);
                } else if (s[i-1] == ')' && i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] == '(') {
                    dp[i] = dp[i - 1] + 2 + (i - dp[i - 1] - 2 >= 0 ? dp[i - dp[i - 1] - 2] : 0);
                }
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};