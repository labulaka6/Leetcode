static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 纵向扫描

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        string ans = "";
        if(strs.size() == 0 || strs[0].length() == 0) return ans;
        for(int i = 0; i < strs[0].length(); ++i){
            char c = strs[0][i];
            bool flag = true;
            for(int j = 1; j < strs.size(); ++j){
                if(c != strs[j][i]){
                    flag = false;
                    break;
                }
            }
            if(flag) ans += c;
            else break;
        }
        return ans;
    }
};