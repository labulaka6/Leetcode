static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 暴力法
// 将每个站都当作起始站然后遍历

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        for(int i = 0; i < gas.size(); ++i){
            int g = gas[i] - cost[i];  // 剩余油量
            int j = (i == gas.size()-1) ? 0 : i+1;
            while(g >= 0){
                if(j == i) return j;
                g += gas[j] - cost[j];
                if(j == gas.size()-1) j = 0;
                else j++;
            }
        }
        return -1;
    }
};

// 贪心
// 单次遍历完成
// 如果 sum(gas) < sum(cost) ，那么不可能环行一圈，这种情况下答案是 -1
// 如果 sum(gas) >= sum(cost)，那必然存在解

class Solution {
  public:
  int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int n = gas.size();

    int total_tank = 0;  // 从0号站开始的剩余油量，遍历一圈后相当于sum(gas) - sum(cost)
    int curr_tank = 0;  // 从出发站开始的剩余油量，每次 < 0 时重置为0
    int starting_station = 0;  // 出发站，每次curr_tank < 0时更新
    for (int i = 0; i < n; ++i) {
      total_tank += gas[i] - cost[i];
      curr_tank += gas[i] - cost[i];
      if (curr_tank < 0) {
        starting_station = i + 1;
        curr_tank = 0;
      }
    }
    return total_tank >= 0 ? starting_station : -1;
  }
};

