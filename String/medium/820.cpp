// 首先要理解题意：
// 从0位置开始遍历字符串S，遇到#停止，得到time
// 从2位置开始遍历字符串S，遇到#停止，得到me
// 从5位置开始遍历字符串S，遇到#停止，得到bell
// 问题，编码字符串S（which可以恢复列表）最短能有多短？
// 其次要注意埋下的坑：
// 能够合并的单词必须在另一个单词的尾部，也就是一直到#
// 接下来就好做了

// 暴力法

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        int n = words.size();
        string ans;  // 索引字符串
        string::size_type idx;  // 为了使用find方法
        for(int i = 7; i > 0; --i){  // 长的字符串肯定不会是短的字符串的子串，所以从长的字符串开始遍历
            for(int j = 0; j < n; ++j){  // 遍历
                if(words[j].size() == i){
                    string tem = words[j] + '#';  // 能够合并的单词必须在另一个单词的尾部，也就是一直到#
                    idx = ans.find(tem);  // 查找是否为子串
                    if(idx == string::npos){  // 不是子串
                        ans += tem;  // 放入索引字符串
                    }
                }else{  // 跳过比i长和比i短的字符串
                    continue;
                }
            }
        }
        return ans.size();
    }
};

// 储存后缀
// 由数据范围可知一个单词最多含有 7 个后缀，所以可以枚举单词所有的后缀。
// 对于每个后缀，如果其存在 words 列表中，就将其从列表中删除。
// 为了高效删除，将 words 用哈希集合（HashSet）来存储。

class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        unordered_set<string> good(words.begin(), words.end());  // 初始化容器
        for (const string& word: words) {  // 遍历单词
            for (int k = 1; k < word.size(); ++k) {  // 在容器中删除所有后缀
                good.erase(word.substr(k));
            }
        }

        int ans = 0;
        for (const string& word: good) {
            ans += word.size() + 1;
        }
        return ans;
    }
};

// 字典树

class TrieNode{
    TrieNode* children[26];  // 26叉树
public:
    int count;  // 初始化为0,增加一个子孙结点+1
    TrieNode() {   // 初始化子结点
        for (int i = 0; i < 26; ++i) children[i] = NULL;
        count = 0;
    }
    TrieNode* get(char c) {   // 插入
        if (children[c - 'a'] == NULL) {
            children[c - 'a'] = new TrieNode();
            count++;
        }
        return children[c - 'a'];
    }
};
class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        TrieNode* trie = new TrieNode();
        unordered_map<TrieNode*, int> nodes;  // 记录单词最后一个字母的结点及对应的单词长度

        for (int i = 0; i < words.size(); ++i) {
            string word = words[i];
            TrieNode* cur = trie;
            for (int j = word.length() - 1; j >= 0; --j)
                cur = cur->get(word[j]);
            nodes[cur] = i;
        }

        int ans = 0;
        for (auto& [node, idx] : nodes) {
            if (node->count == 0) {  // 叶子结点
                ans += words[idx].length() + 1;
            }
        }
        return ans;
    }
};

// 反转 + 排序

class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        int N = words.size();
        // 反转每个单词
        vector<string> reversed_words;
        for (string word : words) {
            reverse(word.begin(), word.end());
            reversed_words.push_back(word);
        }
        // 字典序排序
        sort(reversed_words.begin(), reversed_words.end());

        int res = 0;
        for (int i = 0; i < N; i++) {
            if (i+1 < N && reversed_words[i+1].find(reversed_words[i]) == 0) {
                // 当前单词是下一个单词的前缀(反转前的后缀)，丢弃
            } else {
                res += reversed_words[i].length() + 1; // 单词加上一个 '#' 的长度
            }
        }
        return res;
    }
};

// 自定义排序及比较规则
// 不需要额外申请数组reversed_words

class Solution {
public:
    static bool compare(string& s1, string& s2) {  // 字典序排序规则
        int N1 = s1.length();
        int N2 = s2.length();
        for (int i = 0; i < min(N1, N2); i++) {
            char c1 = s1[N1-1-i];
            char c2 = s2[N2-1-i];
            if (c1 != c2) {
                return c1 < c2;
            }
        }
        return N1 < N2;
    }

    int minimumLengthEncoding(vector<string>& words) {
        int N = words.size();
        // 逆序字典序排序
        sort(words.begin(), words.end(), compare);

        int res = 0;
        for (int i = 0; i < N; i++) {
            if (i+1 < N && endsWith(words[i+1], words[i])) {
                // 当前单词是下一个单词的后缀，丢弃
            } else {
                res += words[i].length() + 1; // 单词加上一个 '#' 的长度
            }
        }
        return res;
    }

    bool endsWith(string& s, string& t) {  // 比较规则 t为s后缀
        int N1 = s.length();
        int N2 = t.length();
        if (N1 < N2) {
            return false;
        }
        for (int i = 0; i < N2; i++) {
            if (s[N1-N2+i] != t[i]) {
                return false;
            }
        }
        return true;
    }
};