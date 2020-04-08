// 深度优先搜索(dfs)：
// 想知道网格中每个连通形状的面积，然后取最大值。
// 如果在一个土地上，以 4 个方向探索与之相连的每一个土地（以及与这些土地相连的土地），
// 那么探索过的土地总数将是该连通形状的面积。
// 为了确保每个土地访问不超过一次，每次经过一块土地时，将这块土地的值置为 0。这样就不会多次访问同一土地。

static const auto _ = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
    int dfs(vector<vector<int>>& grid, int cur_i, int cur_j){
        // 这里的前四个条件都是为了在递归调用时遇到边界的情况而设置的
        if(cur_i < 0 || cur_j < 0 || cur_i == grid.size() || cur_j == grid[0].size() || grid[cur_i][cur_j] != 1) 
            return 0;
        grid[cur_i][cur_j] = 0;  // 遍历过的置为0，防止多次遍历
        int di[4] = {0, 0, 1, -1};
        int dj[4] = {1, -1, 0, 0};
        int ans = 1;
        for(int index = 0; index < 4; ++index){
            int next_i = cur_i + di[index], next_j = cur_j + dj[index];
            ans += dfs(grid, next_i, next_j);
        }
        return ans;
    }
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int ans = 0;
        for(int i = 0; i < grid.size(); ++i){
            for(int j = 0; j < grid[0].size(); ++j){
                ans = max(ans, dfs(grid, i, j));
            }
        }
        return ans;
    }
};

// 深度优先搜索(dfs) + 栈：
// 可以用栈来实现深度优先搜索算法。这种方法本质与上面的方法相同，唯一的区别是：
// 上面的方法通过函数的调用来表示接下来想要遍历哪些土地，让下一层函数来访问这些土地。
// 而这种方法把接下来想要遍历的土地放在栈里，然后在取出这些土地的时候访问它们。
// 访问每一片土地时，将对围绕它四个方向进行探索，找到还未访问的土地，加入到栈 stack 中；
// 另外，只要栈 stack 不为空，就说明还有土地待访问，那么就从栈中取出一个元素并访问。

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int ans = 0;
        for (int i = 0; i != grid.size(); ++i)
            for (int j = 0; j != grid[0].size(); ++j) {
                int cur = 0;
                stack<int> stacki;
                stack<int> stackj;
                stacki.push(i);
                stackj.push(j);
                while (!stacki.empty()) {
                    int cur_i = stacki.top(), cur_j = stackj.top();
                    stacki.pop();
                    stackj.pop();
                    if (cur_i < 0 || cur_j < 0 || cur_i == grid.size() || cur_j == grid[0].size() || grid[cur_i][cur_j] != 1)
                        continue;
                    ++cur;
                    grid[cur_i][cur_j] = 0;
                    int di[4] = {0, 0, 1, -1};
                    int dj[4] = {1, -1, 0, 0};
                    for (int index = 0; index != 4; ++index) {
                        int next_i = cur_i + di[index], next_j = cur_j + dj[index];
                        stacki.push(next_i);
                        stackj.push(next_j);
                    }
                }
                ans = max(ans, cur);
            }
        return ans;
    }
};

// 广度优先搜索(bfs)：
// 将上面方法中的栈改为队列就实现了广度优先搜索
// 每次从队首取出土地，并将接下来想要遍历的土地放在队尾
class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int ans = 0;
        for (int i = 0; i != grid.size(); ++i)
            for (int j = 0; j != grid[0].size(); ++j) {
                int cur = 0;
                queue<int> queuei;
                queue<int> queuej;
                queuei.push(i);
                queuej.push(j);
                while (!queuei.empty()) {
                    int cur_i = queuei.front(), cur_j = queuej.front();
                    queuei.pop();
                    queuej.pop();
                    if (cur_i < 0 || cur_j < 0 || cur_i == grid.size() || cur_j == grid[0].size() || grid[cur_i][cur_j] != 1)
                        continue;
                    ++cur;
                    grid[cur_i][cur_j] = 0;
                    int di[4] = {0, 0, 1, -1};
                    int dj[4] = {1, -1, 0, 0};
                    for (int index = 0; index != 4; ++index) {
                        int next_i = cur_i + di[index], next_j = cur_j + dj[index];
                        queuei.push(next_i);
                        queuej.push(next_j);
                    }
                }
                ans = max(ans, cur);
            }
        return ans;
    }
};