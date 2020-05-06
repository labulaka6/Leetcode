static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 先排序再分类

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        int sub = 0;   // 结果vector的下标值
        string tmp;  // 临时string
        unordered_map<string, int> work; // 判断排序后单词是否存在，即字母组成是否一致
        for(auto str:strs){
            tmp =  str;
            sort(tmp.begin(), tmp.end());
            if(work.count(tmp)){
               res[work[tmp]].emplace_back(str);
            }else{
                vector<string> vec(1, str);
                res.emplace_back(vec);
                work[tmp] = sub++;
            }
        }
        return res;
    }
};


// 计数分类
// 首先初始化 key = "0#0#0#0#0#"，数字分别代表 abcde 出现的次数，# 用来分割。
// 这样的话，"abb" 就映射到了 "1#2#0#0#0"。
// "cdc" 就映射到了 "0#0#2#1#0"。
// "dcc" 就映射到了 "0#0#2#1#0"。

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, int> hash;
        vector<vector<string>> res;
        int sub = 0;   // 结果vector的下标值
        for (int i = 0; i < strs.size(); ++i) {
            vector<int> num(26, 0);
            // 记录每个字符的次数
            for (int j = 0; j < strs[i].length(); ++j) {
                num[strs[i][j] - 'a']++;
            }
            //转成 0#2#2# 类似的形式
            string key = "";
            for (int j = 0; j < num.size(); ++j) {
                key = key + to_string(num[j]) + '#';
            }
            if (hash.count(key)) {
                res[hash[key]].emplace_back(str[i]);
            } else {
                vector<string> vec(1, str[i]);
                res.emplace_back(vec);
                hash[key] = sub++;
            }

        }
        return res;
    }
};