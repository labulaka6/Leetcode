// 双指针遍历
static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    bool isSubsequence(string s, string t) {
        int ns = s.size(), nt = t.size();
        if(ns > nt) return false;
        int count = 0, flag =0;  // 记录匹配的字符数，记录t中指针的位置
        for(int i = 0; i < ns; ++i){  // 从第一个字符开始匹配
            for(int j = flag; j < nt; ++j){  // 遍历t中字符
                flag = j + 1;    // 记录上次跳出位置
                if(s[i] == t[j]){   // 匹配(未匹配直接遍历到末尾)
                    count++;
                    break;
                }
            }
            if(flag == nt) break;  // 已经不满足了，没必要继续遍历
        }
        if(count == ns) return true;
        else return false;
    }
};

// 精简版双指针

class Solution {
public:
    bool isSubsequence(string s, string t) {
        if(s.size()==0)return true;
        int a=0;
        int len = s.size();
        for(int i = 0; i < t.size(); ++i){
            if(s[a]==t[i])
                a++;
            if(a==len) return true;
        }
        return false;
    }
};

// 后续挑战
// 建立一个26*x的二维数组，储存字母出现在t中的位置
// 例如dp[0]是一个储存了'a'在t中出现的所有的位置的vector<int>
class Solution {
public:
    bool isSubsequence(string s, string t) {
        vector<vector<int>>dp(26);
        int tag = -1;   // 当前字母所在位置
        for(int i = 0; i < t.size(); ++i)   // 储存所有字母出现的位置
            dp[t[i]-'a'].push_back(i);
        for(int i = 0; i < s.size(); ++i){
            int now = s[i] - 'a';
            int left = 0, right = dp[now].size() - 1;
            while(left < right){     // 二分查找，需要找到当前位置tag后面一个位置(后面最小的那个)出现的字母
                int mid = (left+right)/2;
                if(dp[now][mid] > tag)
                    right = mid;
                else
                    left = mid + 1;
            }
            if(right < left || dp[now][left] < tag) return false;  // 同下
            tag = dp[now][left];  // 这里dp用left或者right判断均可，while结束left=right
        }
        return true;
    }
};

// 动态规划
// dp[i][j]代表了 s的前i个字母组成的子串 是否为 t的前j个字母组成的子串 的子序列
// (前i个 - 最后一个字母的位置为 i-1)
// 当 i > j 时s的前i个字母组成的子串不可能为t的前j个字母组成的子串的子序列 dp[i][j]=false
// 当 s[i-1] == t[j-1]时 dp[i][j] = dp[i-1][j-1]
// 当 s[i-1] != t[j-1]时 dp[i][j] = dp[i][j-1]

class Solution {
public:
    bool isSubsequence(string s, string t) {
        int sl = s.size(), tl = t.size();
        if(sl > tl) return false;
        if(sl == 0) return true;
        bool dp[sl+1][tl+1];
        for(int j = 0; j <= tl; ++j){  // 当i=0即s为空字符串是，s一定是t的子序列
            dp[0][j] = true;
        }
        dp[1][0] = false;  // 初始化dp[1][0]
        for(int i = 1; i <= sl; ++i){
            for(int j = 1; j <= tl; ++j){
                if(i > j)
                    dp[i][j] = false;
                else if(s[i-1] == t[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else
                    dp[i][j] = dp[i][j-1];
            }
        }
        return dp[sl][tl];
    }
};
