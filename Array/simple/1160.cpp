// 遍历

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int countCharacters(vector<string>& words, string chars) {
        int count = 0;  // 记录用到的字符数
        for(int i = 0; i < words.size(); ++i){   // 选取单词
            string tem = chars;   // 每个单词都可以从chars中寻找一遍(后面找的的字符标记为0防止复用)
            int n = words[i].length();  // 单词的字符计数
            for(int j = 0; j < words[i].length(); ++j){  // 选取单词中的每个字符
                for(int k = 0; k < tem.length(); ++k){  // 在words即tem中遍历寻找
                    if(words[i][j] == tem[k]){  //找到匹配字符
                        n--;   // 字符-1
                        tem[k] = '0';  // 标记为0
                        break;
                    }
                }
            }
            if(n == 0){  // 单词中的字符全部找到，记录找到的字符数
                count += words[i].length();
            }
        }
        return count;
    }
};

// 哈希
// 哈希的主要思想是
// 如果 词汇表的单词中字符对应的数量 小于 字母表chars中对应字符的数量
// 则说明字母表中的字符可以拼写出这个单词
class Solution {
public:
    int countCharacters(vector<string>& words, string chars) {
        unordered_map<char, int> chars_cnt;  // 字母表chars的字符字典
        for (char c : chars)
            ++chars_cnt[c];
        int ans = 0;  // 用到的字符数
        for (string word : words) {   // 遍历词汇表
            unordered_map<char, int> word_cnt;  // 单词的字符字典
            for (char c : word)
                ++word_cnt[c];
            bool is_ans = true;   // 是否满足
            for (char c : word)
                if (chars_cnt[c] < word_cnt[c]) {
                    is_ans = false;
                    break;
                }
            if (is_ans)  // 满足
                ans += word.size();
        }
        return ans;
    }
};