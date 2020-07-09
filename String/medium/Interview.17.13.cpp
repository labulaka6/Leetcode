static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 动态规划

class Solution {
public:
    int respace(vector<string>& dictionary, string sentence) {
        unordered_set<string> dic;
        for(string str: dictionary) dic.insert(str);

        int n = sentence.length();
        // dp[i]表示sentence前i个字符[0, i-1]所得结果
        vector<int> dp(n+1, 0);
        for(int i = 1; i <= n; ++i){
            dp[i] = dp[i-1] + 1;  // 先假设当前字符作为单词不在字典中
            for(int j = 0; j < i; ++j){
                if(dic.find(sentence.substr(j, i)) != dic.end()){
                    dp[i] = min(dp[i], dp[j]);
                }
            }
        }
        return dp[n];
    }
};

// 动态规划优化
// 上述代码套了两层循环，缺点就是对于每一个i，它前面的子字符串都被找了个遍，
// 这其中包括一些根本不可能在字典中出现的单词。需要找一个方法提前结束。
// 一种方法是记录字典中每个单词最后一个字符，如果想匹配的字符串的最后一个字母都不在字典里，就没必要再看这个字符串了；
// 此外，即使字符串最后一个字母在词典里，也不用挨个去找[j,i)子字符串是否匹配，即不需要让j从0到i遍历一遍，只要看对应长度的子串在不在词典里即可。

class Solution {
public:
    int respace(vector<string>& dictionary, string sentence) {
        unordered_set<string> dic;
        // <最后一个字符，这样的单词长度有哪些>
        unordered_map<char, unordered_set<int>> map;
        for(string str: dictionary){
            dic.insert(str);
            int len = str.length();
            char c = str[len-1];
            unordered_set<int> set = map[c];
            set.insert(len);
            map[c] = set;
        }

        int n = sentence.length();
        vector<int> dp(n+1, 0);
        for(int i = 1; i <= n; ++i){
            dp[i] = dp[i-1] + 1;
            char c = sentence[i-1];
            if(map.find(c) != map.end()){
                unordered_set<int> lens = map[c];
                // for(int l: lens){
                //     if(i >= l && dic.find(sentence.substr(i-l, l)) != dic.end()){
                //         dp[i] = min(dp[i], dp[i-l]);
                //     }
                // }
                //使用迭代器比直接for each要快些(其实差不多)
                unordered_set<int>::iterator it;
                for(it = lens.begin(); it != lens.end(); ++it){
                    int l = *it;
                    if(i >= l && dic.find(sentence.substr(i-l, l)) != dic.end()){
                        dp[i] = min(dp[i], dp[i-l]);
                    }
                }
            }
        }
        return dp[n];
    }
};

// 字典树

class Trie {
public:
    Trie* next[26] = {nullptr};
    bool isEnd;

    Trie() {
        isEnd = false;
    }

    void insert(string s) {
        Trie* curPos = this;

        for (int i = s.length() - 1; i >= 0; --i) {
            int t = s[i] - 'a';
            if (curPos->next[t] == nullptr) {
                curPos->next[t] = new Trie();
            }
            curPos = curPos->next[t];
        }
        curPos->isEnd = true;
    }
};

class Solution {
public:
    int respace(vector<string>& dictionary, string sentence) {
        int n = sentence.length(), inf = 0x3f3f3f3f;

        Trie* root = new Trie();
        for (auto& word: dictionary) {
            root->insert(word);
        }

        vector<int> dp(n + 1, inf);
        dp[0] = 0;
        for (int i = 1; i <= n; ++i) {
            dp[i] = dp[i - 1] + 1;

            Trie* curPos = root;
            for (int j = i; j >= 1; --j) {
                int t = sentence[j - 1] - 'a';
                if (curPos->next[t] == nullptr) {
                    break;
                } else if (curPos->next[t]->isEnd) {
                    dp[i] = min(dp[i], dp[j - 1]);
                }
                if (dp[i] == 0) {
                    break;
                }
                curPos = curPos->next[t];
            }
        }
        return dp[n];
    }
};