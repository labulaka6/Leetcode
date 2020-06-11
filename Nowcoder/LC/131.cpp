static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 回溯

class Solution {
    vector<vector<string>> res;
    int size;
    bool check(const string& s, int i, int j) {
        while(i < j){
            if(s[i++] != s[j--]) return false;
        }
        return true;
    }
    void backtrack(const string& s, int ps, vector<string>& temp) {
        if (ps >= size) {
            res.push_back(temp);
            return;
        }
        for (int i = ps; i < size; ++i) {
            if (check(s, ps, i)) {
                temp.push_back(s.substr(ps, i-ps+1));
                backtrack(s, i+1, temp);
                temp.pop_back();
            }
        }
    }
public:
    vector<vector<string>> partition(const string& s) {
        size = s.size();
        if (size == 0) return res;
        vector<string> temp;
        backtrack(s, 0, temp);
        return res;
    }
};

// 此题还可结合Leetcode第 5 题：最长回文子串 的思路，利用动态规划把结果先算出来，这样就可以以 O(1) 的时间复杂度直接得到一个子串是否是回文。