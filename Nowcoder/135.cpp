static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 贪心算法
// 规则定义： 设学生 A 和学生 B 左右相邻，A 在 B 左边；
// 左规则： 当 ratings_B > ratings_A时，B 的糖比 A 的糖数量多。
// 右规则： 当 ratings_A > ratings_B时，A 的糖比 B 的糖数量多。
// 相邻的学生中，评分高的学生必须获得更多的糖果 等价于 所有学生满足左规则且满足右规则。
// 算法流程：
// 1.先从左至右遍历学生成绩 ratings，按照以下规则给糖，并记录在 left 中：
//     1.先给所有学生 1 颗糖；
//     2.若 ratings[i] > ratings[i-1]，则第 i 名学生糖比第 i−1 名学生多 1 个。
//     3.若 ratings[i] <= ratings[i-1]，则第 i 名学生糖数量不变。（交由从右向左遍历时处理。）
// 2.经过此规则分配后，可以保证所有学生糖数量 满足 左规则 。
// 3.同理，在此规则下从右至左遍历学生成绩并记录在 right 中，可以保证所有学生糖数量 满足右规则 。
// 最终，取以上 2 轮遍历 left 和 right 对应学生糖果数的 最大值 ，这样则 同时满足左规则和右规则 ，即得到每个同学的最少糖果数量。

class Solution {
public:
    int candy(vector<int>& ratings) {
        vector<int> left(ratings.size(), 1);
        vector<int> right(ratings.size(), 1);
        for(int i = 1; i < ratings.size(); ++i){
            if(ratings[i] > ratings[i - 1]) left[i] = left[i - 1] + 1;
        }
        int count = left[ratings.size() - 1];
        for(int i = ratings.size() - 2; i >= 0; --i) {
            if(ratings[i] > ratings[i + 1]) right[i] = right[i + 1] + 1;
            count += max(left[i], right[i]);
        }
        return count;
    }
};