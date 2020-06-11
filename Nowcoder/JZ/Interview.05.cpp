static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 额外开辟空间

class Solution {
public:
    string replaceSpace(string s) {
        string res;
        for(auto c : s){
            if(c == ' ')
                res += "%20";
            else
                res += c;
        }
        return res;
    }
};

// 无需额外开辟空间，在原字符串扩充位置

class Solution {
public:
    string replaceSpace(string s) {
        int l1 = s.length() - 1;
        // 此处不可用 for(auto c : s){ } 的形式，因为会无限循环下去
        for (int i = 0; i <= l1; ++i) {
            if (s[i] == ' ') s += "00";
        }
        int l2 = s.length() - 1;
        if (l2 <= l1) return s;
        for (int i = l1; i >= 0; --i) {
            if (s[i] == ' ') {
                s[l2--] = '0';
                s[l2--] = '2';
                s[l2--] = '%';
            } else {
                s[l2--] = s[i];
            }
        }
        return s;
    }
};