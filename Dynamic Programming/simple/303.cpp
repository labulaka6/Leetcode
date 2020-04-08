//一般直观解法

static const auto _ = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class NumArray {
    vector<int> num;
public:
    NumArray(vector<int>& nums) {
        num = nums;
    }

    int sumRange(int i, int j) {
        int count = 0;
        for(i; i <= j; i++){
            count += num[i];
        }
        return count;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(i,j);
 */
// 由于题目后边的这段注释，想到赋值构造函数

// 动态规划--缓存--空间换时间
// 说明中提到“会多次调用 sumRange 方法”， 所以每次都逐个相加计算子区间的和不是理想的做法，
// 可以使用sum[i]存储nums前i个元素的和。则可得到i到j子区间的和为sum[j]-sum[i-1]。

static const auto _ = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class NumArray {
    vector<int> dp;
public:
    NumArray(vector<int>& nums) {
        int sum = 0;         // 记录前n项和
        dp.push_back(0);     // 防止越界，将sum[j]-sum[i-1]转化为sum[j]-sum[i-1]
        for(int i = 0; i < nums.size(); i++){
            sum += nums[i];
            dp.push_back(sum);
        }
    }

    int sumRange(int i, int j) {
        return dp[j + 1] - dp[i];     // 如果是dp[j] - dp[i-1]的话i=0时会越界
    }
};