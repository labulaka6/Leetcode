// 动态规划
// 不得不说这题出题的人脱离现实，出题出的垃圾，题意用文字表达的不清晰
// 题目的意思应该是 给出的台阶后还有一个花费为0台阶，相当于楼层顶部，求到这个位置的最小花费
// dp[i]为从底层到第i个台阶的最小花费(cost[0]为第一个台阶，的对应dp[1])
// 则dp[i] = min(dp[i-1] + cost[i-1], dp[i-2]+cost[i-1])
// 即从底层到第i个台阶最小花费只与
// 1.这个台阶的本身花费 2.从底层到第i-1(一步)个台阶的最小花费 3.从底层到第i-2(两步)个台阶的最小花费 
// 有关

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        vector<int> dp(cost.size() + 1, 0);
        if(cost.size() < 3) return 0;
        dp[0] = 0;
        dp[1] = cost[0];
        dp[2] = cost[1];
        for(int i = 3; i < dp.size(); ++i){
            dp[i] = min(dp[i-1] + cost[i-1], dp[i-2]+cost[i-1]);
        }
        return min(dp[cost.size()], dp[cost.size()-1]);
    }
};

// 简化版
// 只需要两个变量来记录i-1,i-2台阶的最小花费

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        if(cost.size() < 3) return 0;
        int a = cost[0], b = cost[1];
        for(int i = 2; i < cost.size(); ++i){
            int c = min(a + cost[i], b + cost[i]);
            a = b;
            b = c;
        }
        return min(a, b);
    }
};