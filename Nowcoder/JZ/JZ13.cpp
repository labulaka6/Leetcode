static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 双指针

class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        while(l < r){
            if(nums[l] % 2 == 0 && nums[r] % 2 == 1) swap(nums[l], nums[r]);
            if(nums[l] % 2 == 1) l++;
            if(nums[r] % 2 == 0) r--;
        }
        return nums;
    }
};