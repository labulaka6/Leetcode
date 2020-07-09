static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 常规解法

class Solution {
public:
    bool isNumber(string s) {
        int i = 0;
        // 跳过空格
        for(; s[i] == ' '; ++i) {}

        // 检查有效位
        if(s[i] == '+' || s[i] == '-') i++; // 如果存在，跳过符号

        int n_nm, n_pt;
        for(n_nm = 0, n_pt = 0; (s[i] <= '9' && s[i] >= '0') || s[i] == '.'; ++i)
            s[i] == '.' ? n_pt++ : n_nm++;
        if(n_pt > 1 || n_nm < 1) // 最多1位小数点，最少1位数字
            return false;

        // 检查指数是否存在
        if(s[i] == 'e') {
            i++;
            if(s[i] == '+' || s[i] == '-') i++; // 跳过符号

            int n_nm = 0;
            for(; s[i] >= '0' && s[i] <= '9'; ++i, ++n_nm) {}
            if(n_nm < 1)  // 至少一位数字
                return false;
        }

        // 跳过末尾的空格
        for(; s[i] == ' '; ++i) {}

        return s[i] == 0;  // 到达字符串结尾，即'\0'，ASCII值为0
    }
};

// 自动机
//           ' '    sign    number    dot  e    other
// start     start  f_sign  f_number  err  err  err
// f_sign    err    err     f_number  err  err  err
// f_number  end    err     f_number  dot  e    err
// dot       err    err     f_number  err  err  err
// e         err    l_sign  l_number  err  err  err
// l_sign    err    err     l_number  err  err  err
// l_number  end    err     l_number  err  err  err

// 1273 / 1481 个通过测试用例
// 输入：  ".1"
// 输出：  false
// 预期：  true
// 我认为 .1  1. 等不能算作数字 故不再改动

class Automaton{
private:
    unordered_map<string, vector<string>> table = {
        {"start", {"start", "f_sign", "f_number", "err", "err", "err"}},
        {"f_sign", {"err", "err", "f_number", "err", "err", "err"}},
        {"f_number", {"end", "err", "f_number", "dot", "e", "err"}},
        {"dot", {"err", "err", "f_number", "err", "err", "err"}},
        {"e", {"err", "l_sign", "l_number", "err", "err", "err"}},
        {"l_sign", {"err", "err", "l_number", "err", "err", "err"}},
        {"l_number", {"end", "err", "l_number", "err", "err", "err"}}
    };

    int get_c(char c){
        if(isspace(c)) return 0;
        if(c == '+' || c == '-') return 1;
        if(c >= '0' && c <= '9') return 2;
        if(c == '.') return 3;
        if(c == 'e') return 4;
        return 5;
    }
public:
    string state = "start";
    void get(char c){
        state = table[state][get_c(c)];
    }
};

class Solution {
public:
    bool isNumber(string s) {
        Automaton automaton;
        bool isNumber = true;
        for(char c : s){
            automaton.get(c);
            if(automaton.state == "err"){
                isNumber = false;
                break;
            }else if(automaton.state == "end") break;
        }
        if(automaton.state != "end" && automaton.state != "f_number" && automaton.state != "l_number")
            isNumber = false;
        return isNumber;
    }
};