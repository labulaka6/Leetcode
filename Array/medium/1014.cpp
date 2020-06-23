static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 暴力解法
// 超出时间限制
// 46 / 52 个通过测试用例

class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& A) {
        int len = A.size();
        int ans = 0;
        for(int i = 0; i < len - 1; ++i){
            for(int j = i + 1; j < len; ++j){
                int tmp = A[i] + A[j] + i - j;
                ans = max(tmp, ans);
            }
        }
        return ans;
    }
};

// 枚举 - 降低时间复杂度
// 得分公式可以拆分成 A[i]+i 和 A[j]-j 两部分，这样对于统计景点 j 答案的时候，
// 由于 A[j]-j 是固定不变的，因此最大化 A[i]+i+A[j]-j 的值其实就等价于
// 求 [0,j-1] 中 A[i]+i 的最大值 mx，景点 j 的答案即为 mx+A[j]-j 。
// 而 mx 的值我们只要从前往后枚举 j 的时候同时维护即可，这样每次枚举景点 j 的时候，
// 寻找使得得分最大的 i 就能从 O(n) 降至 O(1) 的时间复杂度，总时间复杂度就能从 O(n^2) 降至 O(n)。

class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& A) {
        int ans = 0, mx = A[0] + 0;
        for (int j = 1; j < A.size(); ++j) {
            ans = max(ans, mx + A[j] - j);
            // 边遍历边维护
            mx = max(mx, A[j] + j);
        }
        return ans;
    }
};