// 动态规划：
// 定义 dp[i]为考虑前 i 个元素，以第 i 个数字结尾的最长上升子序列的长度，注意 nums[i] 必须被选取。
// 从小到大计算 dp[] 数组的值，在计算 dp[i] 之前，已经计算出 dp[0, i−1] 的值，则状态转移方程为：
// dp[i] = max(dp[j]) + 1, 其中 0 ≤ j < i且 num[j] < num[i]
// 即考虑往 dp[0, i−1] 中最长的上升子序列后面再加一个nums[i]。
// 由于 dp[j] 代表 nums[0, j] 中以 nums[j] 结尾的最长上升子序列，
// 所以如果能从 dp[j] 这个状态转移过来，那么 nums[i] 必然要大于nums[j]，
// 才能将 nums[i] 放在 nums[j] 后面以形成更长的上升子序列。
// 最后，整个数组的最长上升子序列即所有 dp[i] 中的最大值。
// LISlength = max(dp[i]), 其中 0 ≤ i < n

static const auto _ = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n=(int)nums.size();
        if (n == 0) return 0;
        vector<int> dp(n, 0);
        for (int i = 0; i < n; ++i) {
            dp[i] = 1;
            for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};

// 贪心 + 二分查找法(也是基于动态规划，时间复杂度更低):
// 考虑一个简单的贪心，如果要使上升子序列尽可能的长，则需要让序列上升得尽可能慢，
// 因此希望每次在上升子序列最后加上的那个数尽可能的小。

// 基于上面的贪心思路，维护一个数组 d[i] ，表示长度为 i 的最长上升子序列的末尾元素的最小值，
// 用 len 记录目前最长上升子序列的长度，起始时 len 为 1，d[1] = nums[0]。

// 同时可以注意到 d[i] 是关于 i 单调递增的。因为如果 d[j] ≥ d[i] 且 j < i，
// 考虑从长度为 i 的最长上升子序列的末尾删除 i - j 个元素，那么这个序列长度变为 j ，
// 且第 j 个元素 x（末尾元素）必然小于 d[i]，也就小于 d[j]。
// 那么就找到了一个长度为 j 的最长上升子序列，并且末尾元素比 d[j] 小，从而产生了矛盾。
// (因为数组 d[i] ，表示长度为 i 的最长上升子序列的末尾元素的最小值)
// 因此数组 d[] 的单调性得证。

// 依次遍历数组nums[] 中的每个元素，并更新数组 d[] 和 len 的值。
// 如果 nums[i] > d[len] 则更新 len = len + 1，
// 否则在 d[1, len]中找满足 d[i−1] < nums[j] < d[i] 的下标 i，并更新 d[i] = nums[j]。

// 根据 d 数组的单调性，我们可以使用二分查找寻找下标 i，优化时间复杂度。

//总之，思想就是让 d[] 中存储比较小的元素。这样，d[] 未必是真实的最长上升子序列，但长度len是对的。

// 以输入序列 [0, 8, 4, 12, 2] 为例：
// 第一步插入 0，d = [0]；
// 第二步插入 8，d = [0, 8]；
// 第三步插入 4，d = [0, 4]；
// 第四步插入 12，d = [0, 4, 12]；
// 第五步插入 2，d = [0, 2, 12]。
// 最终得到最大递增子序列长度为 3。

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int len = 1, n = (int)nums.size();
        if (n == 0) return 0;
        vector<int> d(n + 1, 0);
        d[len] = nums[0];
        for (int i = 1; i < n; ++i) {
            if (nums[i] > d[len]) d[++len] = nums[i];
            else{
                int l = 1, r = len, pos = 0; // 如果找不到说明所有的数都比 nums[i] 大，此时要更新 d[1]，所以这里将 pos 设为 0
                while (l <= r) {     // 二分查找
                    int mid = (l + r) >> 1;  // (l + r)的二进制值向右位移一位，相当于(l + r)/2
                    if (d[mid] < nums[i]) {
                        pos = mid;
                        l = mid + 1;
                    }
                    else r = mid - 1;
                }
                d[pos + 1] = nums[i];
            }
        }
        return len;
    }
};