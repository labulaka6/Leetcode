// BFS
// 要注意问题的转化
// 不是从1开始找0，而是从0开始找1

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        queue<pair<int, int>> Q;
        int v1[4] = {-1, 1, 0, 0};
        int v2[4] = {0, 0, -1, 1};
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(matrix[i][j] == 0) Q.push(make_pair(i, j));
                else matrix[i][j] = -1;  // 将不是0的位置置为-1可直接在原数组进行操作
            }
        }
        while(!Q.empty()){
            auto [x0, y0] = Q.front();
            Q.pop();
            for(int i = 0; i < 4; ++i){
                int x = x0 + v1[i];
                int y = y0 + v2[i];
                if(x >= 0 && x < m && y >= 0 && y < n && matrix[x][y] == -1){
                    matrix[x][y] = matrix[x0][y0] + 1;
                    Q.push(make_pair(x, y));
                }
            }
        }
        return matrix;
    }
};

// 动态规划
// dist[i][j]为到0的最近距离

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        // 初始化动态规划的数组，所有的距离值都设置为一个很大的数
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX / 2));
        // 如果 (i, j) 的元素为 0，那么距离为 0
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    dist[i][j] = 0;
                }
            }
        }
        // 只有 水平向左移动 和 竖直向上移动，注意动态规划的计算顺序
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i - 1 >= 0) {
                    dist[i][j] = min(dist[i][j], dist[i - 1][j] + 1);
                }
                if (j - 1 >= 0) {
                    dist[i][j] = min(dist[i][j], dist[i][j - 1] + 1);
                }
            }
        }
        // 只有 水平向左移动 和 竖直向下移动，注意动态规划的计算顺序
        for (int i = m - 1; i >= 0; --i) {
            for (int j = 0; j < n; ++j) {
                if (i + 1 < m) {
                    dist[i][j] = min(dist[i][j], dist[i + 1][j] + 1);
                }
                if (j - 1 >= 0) {
                    dist[i][j] = min(dist[i][j], dist[i][j - 1] + 1);
                }
            }
        }
        // 只有 水平向右移动 和 竖直向上移动，注意动态规划的计算顺序
        for (int i = 0; i < m; ++i) {
            for (int j = n - 1; j >= 0; --j) {
                if (i - 1 >= 0) {
                    dist[i][j] = min(dist[i][j], dist[i - 1][j] + 1);
                }
                if (j + 1 < n) {
                    dist[i][j] = min(dist[i][j], dist[i][j + 1] + 1);
                }
            }
        }
        // 只有 水平向右移动 和 竖直向下移动，注意动态规划的计算顺序
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (i + 1 < m) {
                    dist[i][j] = min(dist[i][j], dist[i + 1][j] + 1);
                }
                if (j + 1 < n) {
                    dist[i][j] = min(dist[i][j], dist[i][j + 1] + 1);
                }
            }
        }
        return dist;
    }
};

// 动态规划优化
// 其实只要左上和右下即可

// 左上和右下的不证了，证明右上。
// 在这给出一个性质： 假如距离(i,j)最近的点在(i-a,j+b) a>0,b>0，则距离(i,j+b)最近的点在(i-a,j+b)。
// 用反证法证明： 如果距离(i,j+b)最近的点(x,y)不在(i-a,j+b)，则(i,j+b)和(x,y)距离d<a，
// 这时点(i,j)和(x,y)的距离d'<=b+d<a+b,与假设矛盾。

// 利用这个性质，如果距离(i,j)最近的点在(i-a,j+b) a>0,b>0，
// 在第一个dp时(i,j)没有取得最优值，
// 但在第二个dp时由于(i,j+b)的最优值已经取得(因为这个最优值在他正上方)，
// 所以(i,j)也能取得最优值。
// 左下原理同上

// 简单来说 左上取到了左边和上边的最优解
// 右下取到了右边和下边的最优解

class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        // 初始化动态规划的数组，所有的距离值都设置为一个很大的数
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX / 2));
        // 如果 (i, j) 的元素为 0，那么距离为 0
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    dist[i][j] = 0;
                }
            }
        }
        // 只有 水平向左移动 和 竖直向上移动，注意动态规划的计算顺序
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i - 1 >= 0) {
                    dist[i][j] = min(dist[i][j], dist[i - 1][j] + 1);
                }
                if (j - 1 >= 0) {
                    dist[i][j] = min(dist[i][j], dist[i][j - 1] + 1);
                }
            }
        }
        // 只有 水平向右移动 和 竖直向下移动，注意动态规划的计算顺序
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                if (i + 1 < m) {
                    dist[i][j] = min(dist[i][j], dist[i + 1][j] + 1);
                }
                if (j + 1 < n) {
                    dist[i][j] = min(dist[i][j], dist[i][j + 1] + 1);
                }
            }
        }
        return dist;
    }
};