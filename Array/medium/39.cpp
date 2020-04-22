static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 回溯算法

class Solution {
    vector<vector<int>> res;

    void backtrack(vector<int>& candidates, vector<int>& track, int n, int k, int target) {
        // 和为target
        if (k == target) {
            vector<int> tem = track;  // 特别注意此处需要将track复制到临时数组
            sort(tem.begin(), tem.end());  // 不然sort排序会打乱track原有顺序
            if(find(res.begin(), res.end(), tem) == res.end()){
                res.push_back(tem);
            }
            return;
        }

        if(k > target) return;
        for (int i = 0; i < n; i++) {
            // 做选择
            track.push_back(candidates[i]);
            backtrack(candidates, track, n, k+candidates[i], target);
            // 撤销选择
            track.pop_back();
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> track;
        int n = candidates.size();
        backtrack(candidates, track, n, 0, target);
        return res;
    }
};