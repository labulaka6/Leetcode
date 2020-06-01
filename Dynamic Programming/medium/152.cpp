static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 动态规划
// 遍历数组时计算当前最大值，不断更新
// 令imax为当前最大值，则当前最大值为 imax = max(imax * nums[i], nums[i])
// 由于存在负数，那么会导致最大的变最小的，最小的变最大的。
// 因此还需要维护当前最小值imin，imin = min(imin * nums[i], nums[i])
// 当负数出现时则imax与imin进行交换再进行下一步计算

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int ans = INT_MIN, imax = 1, imin = 1;
        for(int i = 0; i < nums.size(); ++i){
            if(nums[i] < 0) swap(imax, imin);
            imax = max(imax*nums[i], nums[i]);
            imin = min(imin*nums[i], nums[i]);
            ans = max(ans, imax);
        }
        return ans;
    }
};

// 另一种写法

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int maxF = nums[0], minF = nums[0], ans = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            int mx = maxF, mn = minF;
            maxF = max(mx * nums[i], max(nums[i], mn * nums[i]));
            minF = min(mn * nums[i], min(nums[i], mx * nums[i]));
            ans = max(maxF, ans);
        }
        return ans;
    }
};