// 有限状态机
//              ' '     +/-     number      other
// start        start   signed  in_number   end
// signed       end     end     in_number   end
// in_number    end     end     in_number   end
// end          end     end     in_number   end

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Automaton {
    string state = "start";  // 初始状态
    unordered_map<string, vector<string>> table = {
        {"start", {"start", "signed", "in_number", "end"}},
        {"signed", {"end", "end", "in_number", "end"}},
        {"in_number", {"end", "end", "in_number", "end"}},
        {"end", {"end", "end", "end", "end"}}
    };

    int get_col(char c) {
        if (isspace(c)) return 0;  // 返回第一项
        if (c == '+' or c == '-') return 1;  // 返回第二项
        if (isdigit(c)) return 2;  // 返回第三项
        return 3;  // 返回第四项
    }
public:
    int sign = 1;  // 符号
    long long ans = 0;

    void get(char c) {
        state = table[state][get_col(c)];
        if (state == "in_number") {
            ans = ans * 10 + c - '0';
            ans = sign == 1 ? min(ans, (long long)INT_MAX) : min(ans, -(long long)INT_MIN);// 转为无符号数
        }
        else if (state == "signed")
            sign = c == '+' ? 1 : -1;  // +为1,-为-1
    }
};

class Solution {
public:
    int myAtoi(string str) {
        Automaton automaton;
        for (char c : str)
            automaton.get(c);
        return automaton.sign * automaton.ans;
    }
};

// 利用stringstream

class Solution {
public:
    int myAtoi(string str) {
        int n;
        n = str.find_first_not_of(" ");
        if(n == string::npos)
            return 0;
        if(str[n] == '-' || str[n] == '+' || str[n] >= '0' && str[n] <= '9'){
            int i = str.find_first_not_of("0123456789", n+1);
            if(i != string::npos){
                str.erase(i, str.size());
            }
        }else{
            return 0;
        }
        stringstream s;
        s << str;
        int re;
        s >> re;
        return re;
    }
};

// 超简洁版 - 用stringstream其实不用做那么多判断

class Solution {
public:
    int myAtoi(string str) {
            int d=0;
            istringstream is(str);
            is>>d;
            return d;
        }
};

// 正则表达式(暂未通过 输出为0 初步应该是判断smatch类型转string出问题)

class Solution {
public:
    int myAtoi(string str) {
        regex pattern("[+-]?\\d+");
        smatch result;
        bool ismatch = regex_search(str, result, pattern);
        if(!ismatch) return 0;
        string res =  result[0];
        int flag = 0;
        if(res[0] == '-'){
            flag = -1;
        }else if(res[0] == '+'){
            flag = 1;
        }
        if(flag != 0){
            res = res.substr(1, res.size());
        }
        long long ans = 0;
        for(int i = 0; i < res.size(); ++i){
            ans = ans * 10 + res[i] - '0';
        }
        ans = flag == 1 ? min(ans, (long long)INT_MAX) : min(ans, -(long long)INT_MIN);// 转为无符号数
        return ans*flag;
    }
};