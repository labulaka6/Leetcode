// 直观解法

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int m = board.size();
        int n = board[0].size();
        int v1[8] = {-1, -1, -1, 0, 0, 1, 1, 1};  // 定义八个方向
        int v2[8] = {-1, 0, 1, -1, 1, -1, 0, 1};  // 定义八个方向
        queue<int> Q;  // 利用队列存放发生变化的位置，这样可以省去直接复制数组所造成的内存浪费
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                int cnt = 0;   // 周围活细胞数目
                for(int v = 0; v < 8; v++){
                    int x = i + v1[v];
                    int y = j + v2[v];
                    if(x >= 0 && x < m && y >= 0 && y < n && board[x][y] == 1) cnt++;
                }
                if(board[i][j] == 1){  // 中心位置为活细胞
                    if(cnt < 2){
                        Q.push(i);
                        Q.push(j);
                    }
                    else if(cnt > 3){
                        Q.push(i);
                        Q.push(j);
                    }
                }else if(board[i][j] == 0){   // 中心位置为死细胞
                    if(cnt == 3){
                        Q.push(i);
                        Q.push(j);
                    }
                }
            }
        }
        while(!Q.empty()){  // 发生变化的位置进行改变
            int i = Q.front();
            Q.pop();
            int j = Q.front();
            Q.pop();
            if(board[i][j] == 0) board[i][j] = 1;
            else if(board[i][j] == 1) board[i][j] = 0;
        }
    }
};

// 复合状态

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int m = board.size();
        int n = board[0].size();
        int v1[8] = {-1, -1, -1, 0, 0, 1, 1, 1};  // 定义八个方向
        int v2[8] = {-1, 0, 1, -1, 1, -1, 0, 1};  // 定义八个方向
        queue<int> Q;  // 利用队列存放发生变化的位置，这样可以省去直接复制数组所造成的内存浪费
        for(int i = 0; i < m; ++i){
            for(int j = 0; j < n; ++j){
                int cnt = 0;   // 周围活细胞数目
                for(int v = 0; v < 8; v++){
                    int x = i + v1[v];
                    int y = j + v2[v];
                    if(x >= 0 && x < m && y >= 0 && y < n && (board[x][y] == 1 || board[x][y] == -1)) cnt++;
                }
                if(board[i][j] == 1){  // 中心位置为活细胞
                    if(cnt < 2){
                        board[i][j] = -1;  // -1代表本来活着下一轮死去
                    }
                    else if(cnt > 3){
                        board[i][j] = -1;
                    }
                }else if(board[i][j] == 0){   // 中心位置为死细胞
                    if(cnt == 3){
                        board[i][j] = 2;  // 2代表本轮死去下一轮复活
                    }
                }
            }
        }
        for(int i = 0; i < m; ++i) {  // 重新遍历将值变回来
            for(int j = 0; j < n; ++j) {
                if(board[i][j] > 0) {
                    board[i][j] = 1;
                }else{
                    board[i][j] = 0;
                }
            }
        }
    }
};

// 位运算原地操作
// 一个 int 有 32 bit，输入数据只用了一个 bit，所以可以利用其他空闲的bit位进行“原地修改”。

class Solution {
public:
    void gameOfLife(vector<vector<int>>& board) {
        int dx[] = {-1,  0,  1, -1, 1, -1, 0, 1};
        int dy[] = {-1, -1, -1,  0, 0,  1, 1, 1};

        for(int i = 0; i < board.size(); i++) {
            for(int j = 0 ; j < board[0].size(); j++) {
                int sum = 0;
                for(int k = 0; k < 8; k++) {
                    int nx = i + dx[k];
                    int ny = j + dy[k];
                    if(nx >= 0 && nx < board.size() && ny >= 0 && ny < board[0].size()) {
                        sum += (board[nx][ny]&1); // 只累加最低位
                    }
                }
                if(board[i][j] == 1) {
                    if(sum == 2 || sum == 3) {
                        board[i][j] |= 2;  // 使用第二个bit标记是否存活
                    }
                } else {
                    if(sum == 3) {
                        board[i][j] |= 2; // 使用第二个bit标记是否存活
                    }
                }
            }
        }
        for(int i = 0; i < board.size(); i++) {
            for(int j = 0; j < board[i].size(); j++) {
                board[i][j] >>= 1; //右移一位，用第二bit覆盖第一个bit。
            }
        }
    }
};