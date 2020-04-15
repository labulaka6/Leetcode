// 直接遍历
// 解答错误 - 输出顺序与答案不一致

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int len = nums.size();
        vector<vector<int>> ans;
        for(int i = 1; i <= len; ++i){
            for(int j = 0; j <= len - i; ++j){
                vector<int> tem;
                for(int k = j; k < j + i; ++k){
                    tem.push_back(nums[k]);
                }
                ans.push_back(tem);
            }
        }
        ans.push_back({});
        return ans;
    }
};

// 动态规划思想
// 知道前i-1个元素的全部子集
// 在所有子集(包括{}空集)后加上第i个元素 即为 前i个元素中包含第i个元素的子集
// 再加上不包含第i个元素的子集 即为 前i个元素的全部子集

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int len = nums.size();
        vector<vector<int>> ans;
        ans.push_back({});
        for(int i = 0; i < len; ++i){
            int m = ans.size();
            for(int j = 0; j < m; ++j){
                vector<int> tem = ans[j];
                tem.push_back(nums[i]);
                ans.push_back(tem);
            }
        }
        return ans;
    }
};

// 另一种写法 - 递归

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        // base case，返回一个空集
        if (nums.empty()) return {{}};
        // 把最后一个元素拿出来
        int n = nums.back();
        nums.pop_back();
        // 先递归算出前面元素的所有子集
        vector<vector<int>> res = subsets(nums);

        int size = res.size();
        for (int i = 0; i < size; i++) {
            // 然后在之前的结果之上追加
            res.push_back(res[i]);
            res.back().push_back(n);
        }
        return res;
    }
};

// 回溯算法

class Solution {
public:
    vector<vector<int>> res;

    vector<vector<int>> subsets(vector<int>& nums) {
        // 记录走过的路径
        vector<int> track;
        backtrack(nums, 0, track);
        return res;
    }

    void backtrack(vector<int>& nums, int start, vector<int>& track) {
        res.push_back(track);
        // 注意 i 从 start 开始递增
        for (int i = start; i < nums.size(); i++) {
            // 做选择
            track.push_back(nums[i]);
            // 回溯
            backtrack(nums, i + 1, track);
            // 撤销选择
            track.pop_back();
        }
    }
};