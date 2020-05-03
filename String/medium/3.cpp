static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 滑动窗口

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if(s.size() == 0) return 0;
        unordered_set<char> lookup;  // hash表记录窗口内的字符
        int maxStr = 0;  // 解
        int left = 0;  // 窗口最左端，左指针
        for(int i = 0; i < s.size(); ++i){
            while (lookup.find(s[i]) != lookup.end()){  // 窗口最右端的下一个字符与窗口中出现的某个字符重复
                lookup.erase(s[left]);  // 从窗口中移除最左端字符
                left ++;  // 窗口最左端后移一位
                // 从窗口左端开始一直移除到窗口中没有重复字符为止
                // 相当于窗口内永远是以窗口最右端字符为结尾的最大无重复字符子串
            }
            maxStr = max(maxStr, i-left+1);  // 更新最大值
            lookup.insert(s[i]);  // 记录窗口内的字符
        }
        return maxStr;
    }
};