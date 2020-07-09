static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 双指针

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res;
        int i = 0, j = nums.size() - 1;
        while(i < j){
            int tmp = nums[i] + nums[j];
            if(tmp < target) i++;
            else if(tmp > target) j--;
            else{
                res.emplace_back(nums[i]);
                res.emplace_back(nums[j]);
                break;
            }
        }
        return res;
    }
};