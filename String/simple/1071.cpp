// 看到标题里面有最大公因子这个词，于是先默写一下 gcd 算法
// const gcd = (a, b) => (0 === b ? a : gcd(b, a % b))
// 总有一种好像顺手就能用上的感觉

// 其实看起来两个字符串之间能有这种神奇的关系是挺不容易的，我们希望能够找到一个简单的办法识别是否有解。
// 如果它们有公因子 abc，那么 str1 就是 m 个 abc 的重复，str2 是 n 个 abc 的重复，
// 连起来就是 m+n 个 abc，好像 m+n 个 abc 跟 n+m 个 abc 是一样的。
// 所以如果 str1 + str2 === str2 + str1 就意味着有解。
// 也很容易想到 str1 + str2 !== str2 + str1 也是无解的充要条件。

// 当确定有解的情况下，最优解是长度为 gcd(str1.length, str2.length) 的字符串。(且从头开始)
// 这个理论最优长度是不是每次都能达到呢？是的。
// 因为如果能循环以它的约数为长度的字符串，自然也能够循环以它为长度的字符串，所以这个理论长度就是我们要找的最优解。
// 把刚刚写的那些拼起来就是解法了。
static const auto _ = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    string gcdOfStrings(string str1, string str2) {
        string ans = "";
        int len = 0;
        if(str1 + str2 == str2 + str1){
            if(str1.size() >= str2.size()){
                len = gcd(str1.size(), str2.size());
            }else{
                len = gcd(str2.size(), str1.size());
            }
            ans = str1.substr(0, len);
        }
        return ans;
    }
    int gcd(int a, int b){
        return b == 0 ? a :gcd(b, a%b);
    }
};

// 将gcd变为内联函数，代码更为简洁，运行速度更快，双100%
// 但是有一点缺陷，未判断str1与str2长度
// gcd算法a为较大的数，b为较小的数
class Solution {
public:
    inline int gcd(int a, int b) {return b == 0? a : gcd(b , a % b);}
    string gcdOfStrings(string str1, string str2) {
        if (str1 + str2 != str2 + str1) return "";
        return str1.substr(0, gcd(str1.size(), str2.size()));
    }
};


// 笨办法：枚举法
// 首先答案肯定是字符串的某个前缀，然后简单直观的想法就是枚举所有的前缀来判断，设这个前缀串长度为lenx
// str1 的长度为 len1 ，str2 的长度为 len2
​// 则前缀串的长度必然要是两个字符串长度的约数才能满足条件，否则无法经过若干次拼接后得到长度相等的字符串，
// 公式化来说，即
// len1 mod lenx == 0
// len2 mod lenx == 0
// 所以可以枚举符合长度条件的前缀串，再去判断这个前缀串拼接若干次以后是否等于 str1 和 str2 即可。
// 由于题目要求最长的符合要求的字符串 X，所以可以按长度从大到小枚举前缀串，这样碰到第一个满足条件的前缀串返回即可。

class Solution {
    bool check(string t,string s){
        int lenx = (int)s.length() / (int)t.length();
        string ans = "";
        for (int i = 1; i <= lenx; ++i){
            ans = ans + t;
        }
        return ans == s;
    }
public:
    string gcdOfStrings(string str1, string str2) {
        int len1 = (int)str1.length(), len2 = (int)str2.length();
        for (int i = min(len1, len2); i >= 1; --i){ // 从长度大的开始枚举
            if (len1 % i == 0 && len2 % i == 0){
                string X = str1.substr(0, i);
                if (check(X, str1) && check(X, str2)) return X;
            }
        }
        return "";
    }
};


