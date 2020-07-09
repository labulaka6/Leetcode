static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 排序
// 根据题意，此 55 张牌是顺子的 充分条件 如下：
// 除大小王外，所有牌 无重复 ；
// 设此 55 张牌中最大的牌为 max ，最小的牌为 min （大小王除外），则需满足：
// max - min < 5
// 因而，可将问题转化为：此 55 张牌是否满足以上两个条件？

class Solution {
public:
    bool isStraight(vector<int>& nums) {
        int joker = 0;
        sort(nums.begin(), nums.end()); // 数组排序
        for(int i = 0; i < 4; i++) {
            if(nums[i] == 0) joker++; // 统计大小王数量
            else if(nums[i] == nums[i + 1]) return false; // 若有重复，提前返回 false
        }
        return nums[4] - nums[joker] < 5; // 最大牌 - 最小牌 < 5 则可构成顺子
    }
};

// 若不能使用排序
// 则可遍历一遍，在遍历的过程中记录最大值与最小值，并利用unordered_set查验是否重复