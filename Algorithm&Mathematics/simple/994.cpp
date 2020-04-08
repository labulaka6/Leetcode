//广度优先搜索(bfs)

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
    int cnt;   // 新鲜橘子的个数
    int dis[10][10];  // 坐标位于x,y的橘子的腐烂时间<=>距离
    int dir_x[4]={0, 1, 0, -1};
    int dir_y[4]={1, 0, -1, 0};
public:
    int orangesRotting(vector<vector<int>>& grid) {
        queue<pair<int,int> >Q;
        memset(dis, -1, sizeof(dis));  // 假设橘子都是新鲜的，时间置为-1
        cnt = 0;
        int n=(int)grid.size(), m=(int)grid[0].size(), ans = 0;
        for (int i = 0; i < n; ++i){   // 遍历箱子
            for (int j = 0; j < m; ++j){
                if (grid[i][j] == 2){   // 腐烂的橘子入队
                    Q.push(make_pair(i, j));
                    dis[i][j] = 0;   // 本来就腐烂的橘子，即0时刻就腐烂的橘子
                }
                else if (grid[i][j] == 1) cnt += 1;  // 新鲜橘子
            }
        }
        while (!Q.empty()){
            pair<int,int> x = Q.front();  // 腐烂橘子出队
            Q.pop();
            for (int i = 0; i < 4; ++i){  // 从腐烂橘子开始一轮bfs
                int tx = x.first + dir_x[i];
                int ty = x.second + dir_y[i];
                if (tx < 0|| tx >= n || ty < 0|| ty >= m|| ~dis[tx][ty] || !grid[tx][ty]) continue;
                //~(-1)=0,其余数字取反不等于0，即~dis[tx][ty]等价于dis[tx][ty]!=-1
                //前四个条件为处理边界，grid=0为箱子对应位置没有橘子，dis[tx][ty]!=-1为探索过的橘子
                dis[tx][ty] = dis[x.first][x.second] + 1;  // 这轮搜索到的橘子腐烂的时间为上轮+1
                Q.push(make_pair(tx, ty));  // 这轮腐烂的橘子入队
                if (grid[tx][ty] == 1){
                    cnt -= 1;  // 新鲜橘子-1
                    ans = dis[tx][ty];  // ans会被一直更新直到最后一轮，即最长时间
                    if (!cnt) break;  // 新鲜橘子数量为0，停止
                }
            }
        }
        return cnt ? -1 : ans;
    }
};


class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int min = 0, fresh = 0;  // 时间 ， 新鲜橘子数量
        queue<pair<int, int>> q;
        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid[0].size(); j++)
                if(grid[i][j] == 1) fresh++;   // 新鲜橘子数量+1
                else if(grid[i][j] == 2) q.push({i, j});  // 腐烂橘子入队
        }
        vector<pair<int, int>> dirs = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };  // 左右下上四个方向
        while(!q.empty()) {
            int n = q.size();  // 队列中腐烂橘子数量
            bool rotten = false;   // 是否腐烂
            for(int i = 0; i < n; i++) {
                auto x = q.front();
                q.pop();
                for(auto cur: dirs) {
                    int i = x.first + cur.first;
                    int j = x.second + cur.second;
                    // 在箱子里且为新鲜橘子
                    if(i >= 0 && i < grid.size() && j >= 0 && j < grid[0].size() && grid[i][j] == 1) {
                        grid[i][j] = 2;  // 变腐烂
                        q.push({i, j});  // 入队
                        fresh--;  // 新鲜橘子数量-1
                        rotten = true;  // 腐烂
                    }
                }
            }
            if(rotten) min++;  // 一轮只要有一个新鲜橘子变腐烂则时间+1
        }
        return fresh ? -1 : min;
    }
};