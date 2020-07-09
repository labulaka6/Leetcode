static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 哈希表

class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> m;
        for(char c : s){
            m[c]++;
        }
        for(int i = 0; i < s.length(); ++i){
            if(m[s[i]] == 1) return i;
        }
        return -1;
    }
};