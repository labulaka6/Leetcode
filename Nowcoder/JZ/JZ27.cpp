static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 回溯

class Solution {
public:
    vector<string> permutation(string s) {
        if(s.empty()) return {};
        // 对字符串进行排序
        sort(s.begin(), s.end());
        vector<string> res;
        // 标记字符是否遍历过
        vector<bool> visit(s.size(), false);
        string track;
        backtrack(res, s, track, visit);

        return res;
    }
        /*
        * 回溯函数
        * 使用sort函数对字符串排序，使重复的字符相邻，
        * 使用visit数组记录遍历决策树时每个节点的状态，
        * 节点未遍历且相邻字符不是重复字符时，
        * 则将该字符加入排列字符串中，依次递归遍历。
        */
    void backtrack(vector<string> &res, string s, string &track, vector<bool> &visit) {
        // 回溯结束条件
        if(track.size() == s.size()){
            res.push_back(track);
            return;
        }

        // 选择和选择列表
        for(int i = 0; i < s.size(); i++){
            // 剪枝
            if(visit[i]) continue;
            if(i > 0 && !visit[i-1] && s[i-1] == s[i]) continue;

            visit[i] = true;
            track.push_back(s[i]);
            backtrack(res, s, track, visit);
            track.pop_back();
            visit[i] = false;
        }
    }
};