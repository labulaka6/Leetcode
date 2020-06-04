static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 动态规划
// 超出时间限制 31 / 36 个通过测试用例

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordDictSet;
        for(int i = 0; i < wordDict.size(); ++i){
            wordDictSet.insert(wordDict[i]);
        }
        vector<vector<string>> dp(s.length() + 1);
        vector<string> initial;
        initial.push_back("");
        dp[0] = initial;
        for (int i = 1; i <= s.length(); ++i) {
            vector<string> list;
            for (int j = 0; j < i; ++j) {
                if (dp[j].size() > 0 && wordDictSet.find(s.substr(j, i-j)) != wordDictSet.end()) {
                    for (string l : dp[j]) {
                        list.push_back(l + (l == "" ? "" : " ") + s.substr(j, i-j));
                    }
                }
            }
            dp[i] = list;
        }
        return dp[s.length()];
    }
};

// 回溯

class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_map<string, vector<string>> m;  // 用来剪枝
        return helper(m, wordDict, s);
    }
    vector<string> helper(unordered_map<string,vector<string> >& m, vector<string>& wordDict, string s){
        if(m.count(s)) return m[s];  // 剪枝
        if(s.empty()) return {""};
        vector<string> res;
        for(string word:wordDict){
            if(s.substr(0, word.length()) != word) continue;
            vector<string> tmp = helper(m, wordDict, s.substr(word.length()));  // substr()方法只有一个参数时代表从此处开始一直到结尾
            for(auto itm:tmp){
                res.push_back(word + (itm.empty() ? "": " " + itm));
            }
        }
        m[s] = res;  // 记录字符串s的不同组合，用来剪枝
        return res;
    }
};