// 遍历
// 算出每个位置的表面积，然后再减去贴合的表面积
static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
    // 判断边界
    int limit(vector<vector<int>>& grid, int m, int n, int i, int j){
        int ans = 0;
        if(grid[i][j] > 0){  // 各四个侧面和上下两个面
            ans = 4*grid[i][j] + 2;
        }else{
            return ans;
        }

        if(m < 2 || n < 2){  // 只有一个位置
            return ans;
        }else if(i == 0 && j == 0){  // 左上角
            ans = ans - min(grid[i][j], grid[i+1][j]) - min(grid[i][j], grid[i][j+1]);
        }else if(i == 0 && j == n-1){  // 右上角
            ans = ans - min(grid[i][j], grid[i+1][j]) - min(grid[i][j], grid[i][j-1]);
        }else if(i == m-1 && j == n-1){  // 右下角
            ans = ans - min(grid[i][j], grid[i-1][j]) - min(grid[i][j], grid[i][j-1]);
        }else if(i == m-1 && j == 0){  // 左下角
            ans = ans - min(grid[i][j], grid[i-1][j]) - min(grid[i][j], grid[i][j+1]);
        }else if(i == 0){  // 第一行
            ans = ans - min(grid[i][j], grid[i+1][j]) - min(grid[i][j], grid[i][j-1]) - min(grid[i][j], grid[i][j+1]);
        }else if(i == m-1){  // 最后一行
            ans = ans - min(grid[i][j], grid[i-1][j]) - min(grid[i][j], grid[i][j-1]) - min(grid[i][j], grid[i][j+1]);
        }else if(j == 0){  // 第一列
            ans = ans - min(grid[i][j], grid[i-1][j]) - min(grid[i][j], grid[i+1][j]) - min(grid[i][j], grid[i][j+1]);
        }else if(j == n-1){  // 最后一列
            ans = ans - min(grid[i][j], grid[i-1][j]) - min(grid[i][j], grid[i+1][j]) - min(grid[i][j], grid[i][j-1]);
        }else{  // 其他
            ans = ans - min(grid[i][j], grid[i-1][j]) - min(grid[i][j], grid[i+1][j]) - min(grid[i][j], grid[i][j+1]) - min(grid[i][j], grid[i][j-1]);
        }
        return ans;
    }
public:
    int surfaceArea(vector<vector<int>>& grid) {
        int m = grid.size();
        if(m == 0) return 0;
        int n = grid[0].size();
        if(n == 0) return 0;
        int ans = 0;
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                ans += limit(grid, m, n, i, j);
            }
        }
        return ans;
    }
};

// 可以进一步简化
// 两个柱体贴合的表面积就是 两个柱体高的最小值*2。

class Solution {
public:
    int surfaceArea(vector<vector<int>>& grid) {
        int n = grid.size(), area = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // 先把grid[i][j]赋值给level，省掉了bound check，可以略微略微略微优化一下耗时...
                int level = grid[i][j];
                if (level > 0) {
                    // 一个柱体中：2个底面 + 所有的正方体都贡献了4个侧表面积
                    area += (level*4) + 2;  // << 2 相当于 *4
                    // 减掉 i 与 i-1 相贴的两份表面积
                    area -= i > 0? min(level, grid[i - 1][j])*2: 0;  // << 1 相当于 *2
                    // 减掉 j 与 j-1 相贴的两份表面积
                    area -= j > 0? min(level, grid[i][j - 1])*2: 0;
                }
            }
        }
        return area;
    }
};
