static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 暴力法 - 样例34超出时间限制

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        int len = T.size();
        for(int i = 0; i < len; ++i){
            int count = 0;
            for(int j = i; j < len; ++j){
                if(T[i] >= T[j]){
                    count++;
                    if(j == len-1) count = 0;
                }
                else break;
            }
            T[i] = count;
        }
        return T;
    }
};

// 栈

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> res(n, 0);
        stack<int> st;
        for (int i = 0; i < temperatures.size(); ++i) {
            while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                auto t = st.top();
                st.pop();
                res[t] = i - t;
            }
            st.push(i);  // 下标入栈(根据下标即可得相应数值)
        }
        return res;
    }
};