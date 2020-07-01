static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 原地哈希
// 要求时间复杂度应为O(n)，并且只能使用常数级别的额外空间。
// 思路
// 1.排序(sort())，时间复杂度不符合
// 2.哈希(unordered_map或者unordered_set)，空间复杂度不符合
// 3.将数组视为哈希表，符合

class Solution {
public:
    int firstMissingPositive(vector<int> &nums) {
        // 将所有数放置在对应位置，平均复杂度为O(n)，每个数只会被放置一次
        for (int i = 0; i < nums.size(); i++) {
            while (nums[i] != i + 1) {
                // 如果这个数不在[0,N+1]这个范围 或者 它已经在自己的位置上
                if (nums[i] <= 0 || nums[i] > nums.size() || nums[i] == nums[nums[i] - 1])
                    break;
                // 将数放置到对应位置上[1,2,3...] 1在0，2在1，以此类推... nums[i] = i+1
                // int idx = nums[i] - 1;
                // nums[i] = nums[idx];
                // nums[idx] = idx + 1;
                swap(nums[i], nums[nums[i]-1]);  // 将nums[i]这个数放置到它自己的位置上，即nums[i]-1处
            }
        }
        for (int i = 0; i < nums.size(); i++) {  // 寻找对应位置
            if (nums[i] != (i + 1)) {
                return (i + 1);
            }
        }
        return (nums.size() + 1);
    }
};