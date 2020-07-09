static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 利用sstream

class Solution {
public:
    string reverseWords(string s) {
        string ans, str;
        stringstream ss(s);
        while (ss >> str) ans.insert(0, str + " ");
        return ans.size() ? string(ans.begin(), ans.end() - 1) : "";
    }
};

// 上述方法耗时会达到50ms+，比较高，主要原因是每次都需要调用insert函数进行“逆序存储“”
// 下面改用“顺序存储逆序输出”，耗时可以降到4~10+ms

class Solution {
public:
    string reverseWords(string s) {
        string ans, str;
        vector<string> tmp;
        stringstream ss(s);
        while (ss >> str) tmp.emplace_back(str);
        for (int i = tmp.size() - 1; i >= 0; i--) ans += tmp[i] + " ";
        return ans.size() ? string(ans.begin(), ans.end() - 1) : "";
    }
};

// 使用栈或双端队列

class Solution {
public:
    string reverseWords(string s) {
        int left = 0, right = s.size() - 1;
        // 去掉字符串开头的空白字符
        while (left <= right && s[left] == ' ') ++left;

        // 去掉字符串末尾的空白字符
        while (left <= right && s[right] == ' ') --right;

        deque<string> d;  // 此处也可用栈
        string word;

        while (left <= right) {
            char c = s[left];
            if (word.size() && c == ' ') {
                // 将单词 push 到队列的头部
                d.push_front(move(word));
                word = "";
            }else if (c != ' ') {
                word += c;
            }
            ++left;
        }
        d.push_front(move(word));

        string ans;
        while (!d.empty()) {
            ans += d.front();
            d.pop_front();
            if (!d.empty()) ans += ' ';
        }
        return ans;
    }
};

// 原地 - 先反转整体再反转单词顺便去空格

class Solution {
public:
    string reverseWords(string s) {
        // 反转整个字符串
        reverse(s.begin(), s.end());

        int n = s.size();
        int idx = 0;
        for (int start = 0; start < n; ++start) {
            if (s[start] != ' ') {
                // 填一个空白字符然后将idx移动到下一个单词的开头位置
                if (idx != 0) s[idx++] = ' ';

                // 循环遍历至单词的末尾，并将单词移动到相应位置
                int end = start;
                while (end < n && s[end] != ' ') s[idx++] = s[end++];

                // 反转整个单词
                reverse(s.begin() + idx - (end - start), s.begin() + idx);

                // 更新start，去找下一个单词
                start = end;
            }
        }
        s.erase(s.begin() + idx, s.end());
        return s;
    }
};