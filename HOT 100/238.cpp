static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 乘积 = 当前数左边的乘积 * 当前数右边的乘积

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> res(nums.size(), 0);
        int k = 1;
        for(int i = 0; i < res.size(); i++){
            res[i] = k;
            k *= nums[i];  // 此时数组存储的是除去当前元素左边的元素乘积
        }
        k = 1;
        for(int i = res.size() - 1; i >= 0; i--){
            res[i] *= k; // k为该数右边的乘积。
            k *= nums[i]; // 此时数组等于左边的 * 该数右边的。
        }
        return res;
    }
};