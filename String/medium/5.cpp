// 暴力解法

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
private:
    bool valid(string& s, int left, int right) {
        // 验证子串 s[left, right] 是否为回文串
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }

public:
    string longestPalindrome(string s) {
        // 特判
        int size = s.size();
        if (size < 2) {
            return s;
        }

        int maxLen = 1;
        string res = s.substr(0, 1);

        // 枚举长度大于等于 2 的子串，只要遇到一个回文，则长度+1重新开始枚举
        for (int i = 1; i < size; ++i) {
            for (int j = 0; j < size - i; ++j) {
                if (valid(s, j, j+i)) {
                    maxLen = i + 1;
                    res = s.substr(j, maxLen);
                    break;
                }
            }
        }
        return res;
    }
};


// 改进版

class Solution {
private:
    bool valid(string& s, int left, int right) {
        // 验证子串 s[left, right] 是否为回文串
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }

public:
    string longestPalindrome(string s) {
        // 特判
        int size = s.size();
        if (size < 2) {
            return s;
        }

        int maxLen = 1;
        string res = s.substr(0, 1);

        // 从长到短枚举
        for (int i = size - 1; i > 0; --i) {
            for (int j = 0; j < size - i; ++j) {
                if (valid(s, j, j+i)) {
                    maxLen = i + 1;
                    res = s.substr(j, maxLen);
                    return res;
                }
            }
        }
        return res;
    }
};

// 动态规划
// dp[i][j] 表示子串 s[i, j] 是否为回文子串。
// dp[i][j] = (s[i] == s[j]) and dp[i + 1][j - 1]

// 分析这个状态转移方程：
// （1）“动态规划”事实上是在填一张二维表格，i 和 j 的关系是 i <= j ，因此，只需要填这张表的上半部分；
// （2）看到 dp[i + 1][j - 1] 就得考虑边界情况。

// 边界条件是：表达式 [i + 1, j - 1] 不构成区间，即长度严格小于 2，
// 即 j - 1 - (i + 1) + 1 < 2 ，整理得 j - i < 3。

// 这个结论很显然：当子串 s[i, j] 的长度等于 2 或者等于 3 的时候，
// 其实只需要判断一下头尾两个字符是否相等就可以直接下结论了。
// 如果子串 s[i + 1, j - 1] 只有 1 个字符，即去掉两头，剩下中间部分只有 1 个字符，当然是回文；
// 如果子串 s[i + 1, j - 1] 为空串，那么子串 s[i, j] 一定是回文子串。
// 因此，在 s[i] == s[j] 成立和 j - i < 3 的前提下，直接可以下结论，dp[i][j] = true，否则才执行状态转移。

// 初始化的时候，单个字符一定是回文串，因此把对角线先初始化为 1，即 dp[i][i] = 1 。
// 事实上，初始化的部分都可以省去。因为只有一个字符的时候一定是回文，dp[i][i] 根本不会被其它状态值所参考。
// 只要一得到 dp[i][j] = true，就记录子串的长度和起始位置，没有必要截取，
// 因为截取字符串也要消耗性能，记录此时的回文子串的“起始位置”和“回文长度”即可。

class Solution {
public:
    string longestPalindrome(string s) {
        int len = s.size();
        if (len < 2) {
            return s;
        }

        bool dp[len][len];
        memset(dp, false, sizeof(dp));

        // 初始化
        for (int i = 0; i < len; i++) {
            dp[i][i] = true;
        }

        int maxLen = 1;   // 最大长度
        int start = 0;    // 起始位置

        for (int j = 1; j < len; ++j) {
            for (int i = 0; i < j; ++i) {
                // 下边这个if-else判断可简化为：
                // dp[i][j] = s.charAt(i) == s.charAt(j) && (j - i < 3 || dp[i + 1][j - 1]);
                if (s[i] == s[j]) {
                    if (j - i < 3) {
                        dp[i][j] = true;
                    } else {
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                } else {
                    dp[i][j] = false;
                }

                // 只要 dp[i][j] == true 成立，就表示子串 s[i, j] 是回文，此时记录回文长度和起始位置
                if (dp[i][j]) {
                    int curLen = j - i + 1;
                    if (curLen > maxLen) {
                        maxLen = curLen;
                        start = i;
                    }
                }
            }
        }
        return s.substr(start, maxLen);
    }
};

// 中心扩散法

class Solution {
private:
    string centerSpread(string& s, int left, int right) {
        // left = right 的时候，此时回文中心是一个字符，向两边扩散得到的回文子串的长度是奇数
        // right = left + 1 的时候，此时回文中心是一个空隙，向两边扩散得到的回文子串的长度是偶数
        int size = s.size();
        int i = left;
        int j = right;
        while (i >= 0 && j < size) {
            if (s[i] == s[j]) {
                i--;
                j++;
            } else {
                break;
            }
        }
        // 这里要小心，跳出 while 循环时，恰好满足 s.charAt(i) != s.charAt(j)，因此不能取 i，不能取 j
        return s.substr(i + 1, j - i - 1);
    }

public:
    string longestPalindrome(string s) {
        // 特判
        int size = s.size();
        if (size < 2) {
            return s;
        }

        int maxLen = 1;  // 最大长度
        string res = s.substr(0, 1);  // 最长回文子串

        // 中心位置枚举到 len - 2 即可
        for (int i = 0; i < size - 1; ++i) {
            string oddStr = centerSpread(s, i, i);
            string evenStr = centerSpread(s, i, i + 1);
            string maxLenStr = oddStr.size() > evenStr.size() ? oddStr : evenStr;
            if (maxLenStr.length() > maxLen) {
                maxLen = maxLenStr.size();
                res = maxLenStr;
            }
        }
        return res;
    }
};

// Manacher 算法

class Solution {
public:
    string preProcess(string s) {
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
    // 马拉车算法
    string longestPalindrome(string s) {
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
        int start = (centerIndex - maxLen) / 2;   // 求原字符串下标
        return s.substr(start, maxLen);
    }
};