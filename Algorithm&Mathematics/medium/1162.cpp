// BFS

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int, int>> Q;
        int v1[4] = {0, 0, -1, 1};  // 定义四个方向
        int v2[4] = {1, -1, 0, 0};  // 定义四个方向
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(grid[i][j] == 1){   // "初始陆地"入队
                    Q.push(make_pair(i, j));
                }
            }
        }
        while(!Q.empty()){
            pair<int, int> tem = Q.front();
            Q.pop();
            for(int i = 0; i < 4; ++i){     // 向四个方向扩散
                int x = tem.first + v1[i];
                int y = tem.second + v2[i];
                // 判断边界及"海洋"
                if(x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 0){
                    Q.push(make_pair(x,y));
                    grid[x][y] = grid[tem.first][tem.second] + 1;
                }
            }
        }
        int max = 0;  // 最远"海洋"
        for(int i = 0; i < grid.size(); ++i){
            for(int j = 0; j < grid[0].size(); ++j){
                if(grid[i][j] > max){
                    max = grid[i][j];
                }
            }
        }
        if(max == 1 || max == 0) return -1;  // 特例
        else return max - 1;
    }
};

// 改进了一点
// 去掉最后的循环

class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int, int>> Q;
        int v1[4] = {0, 0, -1, 1};  // 定义四个方向
        int v2[4] = {1, -1, 0, 0};  // 定义四个方向
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(grid[i][j] == 1){   // "初始陆地"入队
                    Q.push(make_pair(i, j));
                }
            }
        }
        bool hasOcean = false;
        pair<int, int> tem = make_pair(-1, -1);
        while(!Q.empty()){
            tem = Q.front();
            Q.pop();
            for(int i = 0; i < 4; ++i){     // 向四个方向扩散
                int x = tem.first + v1[i];
                int y = tem.second + v2[i];
                // 判断边界及"海洋"
                if(x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 0){
                    Q.push(make_pair(x,y));
                    grid[x][y] = grid[tem.first][tem.second] + 1;
                    hasOcean = true;
                }
            }
        }
        if(tem.first == -1 || !hasOcean) return -1;  // 特例
        else return grid[tem.first][tem.second] - 1;
    }
};

