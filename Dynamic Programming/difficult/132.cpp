static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 回溯
// 超出时间限制  25 / 29 个通过测试用例

class Solution {
    int minx;
    int size;
    bool check(const string& s, int i, int j) {
        while(i < j){
            if(s[i++] != s[j--]) return false;
        }
        return true;
    }
    void backtrack(const string& s, int ps, int cut) {
        if (ps >= size) {
            minx = min(cut, minx);
            return;
        }
        for (int i = ps; i < size; ++i) {
            if (check(s, ps, i)) {
                cut++;
                backtrack(s, i+1, cut);
                cut--;
            }
        }
    }
public:
    int minCut(string s) {
        size = s.size();
        if (size == 0) return 0;
        if(check(s, 0, size-1)) return 0;
        minx = INT_MAX;
        backtrack(s, 0, 0);
        return minx-1;
    }
};

// 动态规划
// dp[j][i]为 [i, j]是否为回文串
// min_s[i]记录到字符串从0到i位置需要分割次数

class Solution {
public:
    int minCut(string s) {
        int n = s.length();
        vector<int> min_s(n, 0);
        vector<vector<bool>> dp(n, vector<bool> (n, false));
        for (int i = 0; i < n; ++i) {
            min_s[i] = i;
            for (int j = 0; j <= i; j++) {
                if (s[i] == s[j] && (i - j < 3 || dp[j + 1][i - 1])) {
                    dp[j][i] = true;
                    min_s[i] = j == 0 ? 0 : min(min_s[i], min_s[j - 1] + 1);
                }
            }
        }
        return min_s[n - 1];
    }
};