static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ans(2);
        ans[0] = 0;
        ans[1] = 1;
        for(int i = 0; i < nums.size()-1; ++i){
            if(nums[ans[0]] + nums[ans[1]] == target) break;
            for(int j = i+1; j < nums.size(); ++j){
                if(nums[i] + nums[j] == target){
                    ans[0] = i;
                    ans[1] = j;
                    break;
                }
            }
        }
        return ans;
    }
};