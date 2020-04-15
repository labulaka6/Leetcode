// 回溯

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
    vector<vector<int>> res;

    void backtrack(vector<int>& nums, vector<int>& track) {
        if(track.size() == nums.size()){
            res.push_back(track);
            return ;
        }

        for (int i = 0; i < nums.size(); i++) {
            if(find(track.begin(), track.end(), nums[i]) != track.end()) continue;
            // 做选择
            track.push_back(nums[i]);
            // 回溯
            backtrack(nums, track);
            // 撤销选择
            track.pop_back();
        }
    }

public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<int> track;
        backtrack(nums, track);
        return res;
    }
};