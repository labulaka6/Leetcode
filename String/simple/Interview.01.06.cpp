
static const auto _ =[](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    string compressString(string S) {
        if(S.length() == 0) return S;  // 字符串为空
        char tem = S[0];    // 临时储存相同字符的第一个
        int count = 0;    // 计数
        string result = "";  // 结果字符串
        for(int i = 0; i < S.length(); ++i){
            if(S[i] == tem){  // 有相同字符
                count++;
            }else{    // 遇到不同字符(下个相同字符字串的第一个)
                string n = to_string(count);
                result += tem + n;  // 拼接结果字符串
                tem = S[i];
                count = 1;
            }
        }
        string n = to_string(count);  //处理最后一个子串
        result = result + tem + n;  //处理最后一个子串
        if(result.length() < S.length()) return result;
        else return S;
    }
};

// 双指针法：和上边思想一样，代码更整齐
class Solution {
public:
    string compressString(string S) {
        int N = S.length();
        string res;
        int i = 0;
        while (i < N) {
            int j = i;
            while (j < N && S[j] == S[i]) {  //字串字符个数为j-i
                j++;
            }
            res += S[i];
            res += to_string(j - i);
            i = j;
        }

        if (res.length() < S.length()) {
            return res;
        } else {
            return S;
        }
    }
};

