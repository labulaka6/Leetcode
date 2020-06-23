static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 模拟二进制竖式加法

class Solution {
public:
    string addBinary(string a, string b) {
        string s;
		int c = 0, i = a.size() - 1, j = b.size() - 1;
		while(i >= 0 || j >= 0 || c == 1){
			c += i >= 0 ? a[i--] - '0' : 0;  // a在这一位的贡献(i <= 0则说明a字符串较短，a所有位已经用完，贡献为0)
			c += j >= 0 ? b[j--] - '0' : 0;  // b在这一位的贡献(j <= 0则说明b字符串较短，b所有位已经用完，贡献为0)
			s.push_back((c & 1) + '0');  // 二进制最低位压入字符串(c的二进制表示最多2位)
			c >>= 1;  // 右移一位，剩下的一位为进位位(c的二进制表示最多2位)
		}
		reverse(s.begin(), s.end());  // 翻转
		return s;
    }
};