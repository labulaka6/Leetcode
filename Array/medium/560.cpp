static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 枚举

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int count = 0;
        for (int start = 0; start < nums.size(); ++start) {
            int sum = 0;
            // 按理正着计算与反着计算时间复杂度相同，但是正着计算时间复杂度超出
            // 推测是因为测试用例排布的问题
            // for (int end = start; end < nums.size(); ++end)
            for (int end = start; end >= 0; --end) {
                sum += nums[end];
                if (sum == k) {
                    count++;
                }
            }
        }
        return count;
    }
};

// 前缀和 + 哈希表优化

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int sum = 0, res = 0;
      	// 注意这里前缀和多了一个0，防止漏掉数组的前缀和刚好等于k的情况
        unordered_map<int, int> um{{0, 1}};
        for (int& num : nums) {
            sum += num;  // 前缀和
            res += um[sum - k];  // 记录和为 k 的连续的子数组的个数
            ++um[sum];  // 记录前缀和出现的次数
        }
        return res;
    }
};