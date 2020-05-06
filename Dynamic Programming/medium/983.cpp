static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 倒推

class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int len = days.size(), maxDay = days[len-1], minDay = days[0];
        vector<int> dp(maxDay+31, 0);  // 多扩几天，省得判断 365 的限制
        // 只需看 maxDay -> minDay，此区间外都不需要出门，不会增加费用
        for (int d = maxDay, i = len - 1; d >= minDay; d--) {
            // i 表示 days 的索引
            // 也可提前将所有 days 放入 Set，再通过 set.count() 判断
            if (d == days[i]) {
                dp[d] = min(dp[d+1] + costs[0], dp[d+7] + costs[1]);
                dp[d] = min(dp[d], dp[d+30] + costs[2]);
                i--;  // 别忘了递减一天
            } else dp[d] = dp[d+1];  // 不需要出门
        }
        return dp[minDay];  // 从后向前遍历，返回最前的 minDay
    }
};

// 正推

class Solution {
public:
    int mincostTickets(vector<int>& days, vector<int>& costs) {
        int last = days[days.size()-1];
        vector<int> dp(last+1, 0);
        int idx = 0;
        for (int i = 1; i <= last; i++) {
            if (i == days[idx]) {
                int cost = INT_MAX;
                int oneDayAgo = i-1;
                int sevenDaysAgo = i-7 > 0 ? i-7 : 0;
                int thirtyDaysAgo = i-30 > 0 ? i-30 : 0;

                cost = min(dp[oneDayAgo] + costs[0], cost);
                cost = min(dp[sevenDaysAgo] + costs[1], cost);
                cost = min(dp[thirtyDaysAgo] + costs[2], cost);

                dp[i] = cost;

                idx++;
            } else {
                dp[i] = dp[i-1];
            }
        }

        return dp[last];
    }
};