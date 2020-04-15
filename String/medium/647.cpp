// 暴力解法 - 穷举

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
    bool isSubstring(string s){  // 是否为回文串
        int len = s.length();
        bool ans = true;
        for(int i = 0; i <= (len-1)/2; ++i){
            if(s[i] != s[len-i-1]){
                ans = false;
                break;
            }
        }
        return ans;
    }
public:
    int countSubstrings(string s) {
        int len = s.length();
        if(len == 0) return 0;
        int count = 0;
        for(int i = 1; i <= len; ++i){  // 穷举所有长度的子串
            for(int j = 0; j <= len - i; ++j){
                if(isSubstring(s.substr(j, i))) count++;
            }
        }
        return count;
    }
};

// 中心扩展法
// 可能的中心包括字符及字符之间的间隙

class Solution {
public:
    int countSubstrings(string s) {
        int n = s.length(), ans = 0;
        for (int center = 0; center <= 2*n-1; ++center) {
            int left = center / 2;
            int right = left + center % 2;
            while (left >= 0 && right < n && s[left] == s[right]) {
                ans++;
                left--;
                right++;
            }
        }
        return ans;
    }
};

// 动态规划

class Solution {
public:
    int countSubstrings(string s) {
        int len = s.length();
        int res = 0;
        vector<vector<bool>> dp(len, vector<bool> (len, false));
        for (int j = 0; j < len; j++) {
            for (int i = j; i >= 0; i--) {
                // 因为有j - i < 2的判断条件 所以无需初始化
                if (s[i] == s[j] && ((j - i < 2) || dp[i + 1][j - 1])) {
                    dp[i][j] = true;
                    res++;
                }
            }
        }
        return res;
    }
};

// 马拉车算法

class Solution {
    string preProcess(string s) {  // 预处理
        int n = s.size();
        if (n == 0) {
            return "^$";
        }
        string ret = "^";
        for (int i = 0; i < n; i++)
            ret = ret + "#" + s[i];
        ret += "#$";
        return ret;
    }
public:
    int countSubstrings(string s) {
        string T = preProcess(s);
        int n = T.size();
        int P[n];
        memset(P, 0, sizeof(P));
        int C = 0, R = 0;
        for (int i = 1; i < n - 1; ++i) {
            int i_mirror = 2 * C - i;  // i关于C的对称点
            if (R > i) {
                P[i] = min(R - i, P[i_mirror]);  // 防止超出 R
            } else {
                P[i] = 0;  // 等于 R 的情况 或者 遇到左边界
            }

            // 碰到之前讲的三种情况时候，需要利用中心扩展法
            while (T[i + 1 + P[i]] == T[i - 1 - P[i]]) {
                P[i]++;
            }

            // 判断是否需要更新 R
            if (i + P[i] > R) {
                C = i;
                R = i + P[i];
            }
        }
        // 找出 P 的最大值
        int maxLen = 0;
        int centerIndex = 0;
        for (int i = 1; i < n - 1; i++) {
            if (P[i] > maxLen) {
                maxLen = P[i];
                centerIndex = i;
            }
        }
        int ans = 0;
        for(int v: P) ans += (v + 1) / 2;
        return ans;
    }
};