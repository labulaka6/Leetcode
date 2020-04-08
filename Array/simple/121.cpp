// 普通解法--直观解法
// 挨个遍历，输出最大

static const auto _ = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
    int profit = 0;
public:
    int maxProfit(vector<int>& prices) {
        for(int i = 0; i < prices.size(); i++){
            for(int j = i; j < prices.size(); j++){   //时间复杂度高，需1000+ms运行时间
                if(profit < prices[j] - prices[i]){
                    profit = prices[j] - prices[i];
                }
            }
        }
        return profit;
    }
};


// 动态规划解法
// 假设在第i天卖出股票，第i天的最大利润为在[0 , i-1]天中价格最低的时候买入
// 选出最大利润
static const auto _ = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size() == 0) return 0;
        int profit = 0;
        int minDay = prices[0];
        for(int i = 1; i < prices.size(); i++){   //只需一次循环，时间复杂度低，运行时间4ms
            minDay = min(minDay, prices[i]);
            profit = max(profit, prices[i] - minDay);
        }
        return profit;
    }
};
