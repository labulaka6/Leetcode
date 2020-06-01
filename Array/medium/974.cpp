static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 前缀和 + 哈希表

// 子数组的元素之和 => 数组第 i 项到第 j 项的和
// 元素和能被 K 整除的子数组数目 => 有几种 i、j 组合，使得 A[i] 到 A[j] 之和 mod K == 0
// ↓ ↓ ↓ 转化为 ↓ ↓ ↓
// 有几种 i、j 组合，满足 (preSum[j] − preSum[i−1]) mod K == 0
// 有几种 i、j 组合，满足 preSum[j] mod K == preSum[i-1] mod K
// 前提：preSum[j] 、preSum[i-1] 为正整数。负数的情况要处理

// 流程
// (1)预置 preSum[-1] = 0
// -1 代表数组 A 的第 -1 项，即遍历数组 A 之前，map 提前放入 0:1，表示 求第 0 项前缀和之前，
// 前缀和 mod K 等于 0 已经出现了 1 次
// 这是违背现实的，但别纠结，只是为了求出第一个 preSumModK 而已
// (2)遍历数组 A 的每一项，求当前项的 preSumModK ，存入 map 中
// 之前没有存过，则作为 key 存入，值为 1。之前存过，则对应值 +1
// 于是 map 就录入了各项对应的【前缀和 mod K】
// (3)边存 边查看已有的 key ，如果 map 中存在 key 等于 当前 preSumModK
// 说明存在 之前求过的 preSumModK ，等于 当前 preSumModK
// 把 key 对应的出现次数，累加给 count
// 过去的某个前缀和，与当前前缀和搭配，差分出一个子数组
// 出现过几次 ，就是有几个过去的前缀和，与当前前缀和，差分出几个满足条件的子数组

// 前缀和为负数的情况:
// 举例：K = 4，求得一个前缀和为 -1 ， -1 % K = -1 ，3 % K = 3
// 看似模的结果不相等，一个为 -1 一个为 3 ，但它们应该记到一组
// 因为它们前缀和之差：3 - (-1) 为 4 。 4 % K = 0
// 所以 mod K 的结果 -1 ，要加上 K ，转成正数的 3

class Solution {
public:
    int subarraysDivByK(vector<int>& A, int K) {
        unordered_map<int, int> record = {{0, 1}};
        int sum = 0, ans = 0;
        for (int elem: A) {
            sum += elem;
            // 注意 C++ 取模的特殊性，当被除数为负数时取模结果为负数，需要纠正
            int modulus = (sum % K + K) % K;
            if (record.count(modulus)) {
                ans += record[modulus];
            }
            record[modulus]++;
        }
        return ans;
    }
};