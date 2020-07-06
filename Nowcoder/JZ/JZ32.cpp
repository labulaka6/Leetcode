static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 转换为字符串再进行比较
// C++中 string对象的大小比较:两个字符串自左向右逐个字符相比（按ASCII值大小相比较），直到出现不同的字符或遇’\0’为止。

class Solution {
public:
    string minNumber(vector<int>& nums) {
        vector<string> strs;
        string ans;
        for(int i = 0; i < nums.size(); i ++){
            strs.emplace_back(to_string(nums[i]));
        }
        sort(strs.begin(), strs.end(), [](string& s1, string& s2){return s1 + s2 < s2 + s1;});
        for(int i = 0; i < strs.size(); i ++){
            ans += strs[i];
        }
        return ans;
    }
};