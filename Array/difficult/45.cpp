static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 贪心算法
// 每次都寻找可以跳到最远距离的位置

class Solution {
public:
    int jump(vector<int>& nums) {
        int end = 0;
        int maxPosition = 0;
        int steps = 0;
        // i < nums.size() - 1是为了避免走到最后一格再次起跳
        for(int i = 0; i < nums.size() - 1; ++i){
            // 每次探索这个位置能到达的最远距离
            maxPosition = max(maxPosition, nums[i] + i);
            if(i == end){  // 第一步或者遇到上一步能到达的边界，就更新边界，并且步数加一
                end = maxPosition;
                steps++;
            }
        }
        return steps;
    }
};

// 贪心 - 倒推

class Solution {
public:
    int jump(vector<int>& nums) {
        int position = nums.size() - 1;  // 要找的位置
        int steps = 0;
        while (position != 0) {  // 是否到了第 0 个位置
            for (int i = 0; i < position; ++i) {
                if (nums[i] >= position - i) {
                    position = i;  // 更新要找的位置
                    steps++;
                    break;
                }
            }
        }
        return steps;
    }
};