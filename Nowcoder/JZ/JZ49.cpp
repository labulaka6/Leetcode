static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 利用stringstream

class Solution {
public:
    int strToInt(string str) {
        int d = 0;
        stringstream s(str);
        s >> d;
        return d;
    }
};

// 有限状态机
//         ' '    +,-   0-9     other
// start   start  sign  number  end
// sign    end    end   number  end
// number  end    end   number  end
// end     end    end   end     end

class Automaton{
private:
    string state = "start";
    unordered_map<string, vector<string>> table = {
        {"start", {"start", "sign", "number", "end"}},
        {"sign", {"end", "end", "number", "end"}},
        {"number", {"end", "end", "number", "end"}},
        {"end", {"end", "end", "end", "end"}}
    };

    int get_c(char c){
        if(isspace(c)) return 0;
        if(c == '+' || c == '-') return 1;
        if(isdigit(c)) return 2;
        return 3;
    }
public:
    int sign = 1;  // 符号
    long long ans = 0;

    void get(char c){
        state = table[state][get_c(c)];
        if(state == "number"){
            ans = ans * 10 + c - '0';
            ans = sign == 1 ? min(ans, (long long)INT_MAX) : min(ans, -(long long)INT_MIN);
        }else if(state == "sign"){
            sign = c == '+' ? 1 : -1;
        }
    }
};

class Solution {
public:
    int strToInt(string str) {
        Automaton automaton;
        for(char c : str){
            automaton.get(c);
        }
        return automaton.sign * automaton.ans;
    }
};

// 常规解法

class Solution {
public:
    int strToInt(string str) {
        int res = 0;
        int i = 0;
        int flag = 1;
        // 1. 检查空格
        while (str[i] == ' ') { i++; }
        // 2. 检查符号
        if (str[i] == '-') { flag = -1; }
        if (str[i] == '+' || str[i] == '-') { i++; }
        // 3. 计算数字
        while (i < str.size() && isdigit(str[i])) {
            int r = str[i] - '0';
            // ------ 4. 处理溢出，这是关键步骤 ------
            // int范围 -2147483648 ~ 2147483647
            if (res > INT_MAX / 10 || (res == INT_MAX / 10 && r > 7)) {
                return flag > 0 ? INT_MAX : INT_MIN;
            }
            // ------------------------------------
            res = res * 10 + r;
            i++;
        }
        return flag > 0 ? res : -res;
    }
};