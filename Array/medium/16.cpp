static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 排序 + 双指针
// 排序后先确定一个值，然后双指针寻找最接近的三个数

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int ans = nums[0] + nums[1] + nums[2];
        for(int i = 0; i < nums.size()-2; ++i) {
            int start = i+1, end = nums.size() - 1;
            while(start < end) {
                int sum = nums[start] + nums[end] + nums[i];
                if(abs(target - sum) < abs(target - ans)) ans = sum;
                if(sum > target) end--;
                else if(sum < target) start++;
                else return ans;
            }
        }
        return ans;
    }
};