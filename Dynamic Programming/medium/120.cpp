// 动态规划 - 自顶向下
// 依次计算每一层到每个位置的最小路径和
// 最后返回最后一层最小的最小路径和即可
// 直接在原数组进行计算
static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size();
        for(int i = 1; i < n; ++i){
            for(int j = 0; j <= i; ++j){
                if(j == 0){  // 左边界
                    triangle[i][j] += triangle[i-1][j];
                }else if(j == i){  // 右边界
                    triangle[i][j] += triangle[i-1][j-1];
                }else{
                    triangle[i][j] += min(triangle[i-1][j-1], triangle[i-1][j]);
                }
            }
        }
        return *min_element(triangle[n-1].begin(), triangle[n-1].end());
    }
};

// 动态规划 - 自下向上

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int row = triangle.size();
        vector<int> minlen(row+1, 0);
        for (int level = row - 1; level >= 0; --level){
            for (int i = 0; i <= level; ++i){   //第i行有i+1个数字
                minlen[i] = min(minlen[i], minlen[i+1]) + triangle[level][i];
            }
        }
        return minlen[0];
    }
};