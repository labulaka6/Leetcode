static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 动态规划
// 1.初始化dp = [False,⋯,False]，长度为n+1。n为字符串长度。dp[i]表示s的前i位是否可以用wordDict中的单词表示。
// 2.初始化dp[0]=True，空字符可以被表示。
// 3.遍历字符串的所有子串，遍历开始索引i，遍历区间[0,n)：
//      遍历结束索引j，遍历区间[i+1,n+1)：
//      若 dp[i]=True 且s[i,⋯,j)在wordlistwordlist中：dp[j]=Truedp[j]=True。
//      解释：dp[i]=True 说明s的前i位可以用wordDict表示，则s[i,⋯,j)出现在wordDict中，说明s的前j位可以表示。
// 4.返回dp[n]dp[n]

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordDictSet;
        for(int i = 0; i < wordDict.size(); ++i){
            wordDictSet.insert(wordDict[i]);
        }
        vector<bool> dp(s.length() + 1, false);
        dp[0] = true;
        for (int i = 1; i <= s.length(); i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && wordDictSet.find(s.substr(j, i-j)) != wordDictSet.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[s.length()];
    }
};