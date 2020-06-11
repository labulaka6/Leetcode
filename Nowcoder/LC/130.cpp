static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// DFS
// 先把与边界相连的O改为#，然后再把O变为X，#变为O

class Solution {
    void dfs(vector<vector<char>>& b, int i, int j){
        if (i < 0 || j < 0 || i >= b.size()  || j >= b[0].size() || b[i][j] == 'X' || b[i][j] == '#') {
            // b[i][j] == '#' 说明已经搜索过了.
            return;
        }
        b[i][j] = '#';
        dfs(b, i - 1, j); // 上
        dfs(b, i + 1, j); // 下
        dfs(b, i, j - 1); // 左
        dfs(b, i, j + 1); // 右
    }
public:
    void solve(vector<vector<char>>& board) {
        if (board.size() == 0) return;
        int m = board.size();
        int n = board[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // 从边缘o开始搜索
                bool isEdge = i == 0 || j == 0 || i == m - 1 || j == n - 1;
                if (isEdge && board[i][j] == 'O') {
                    dfs(board, i, j);
                }
            }
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 'O') board[i][j] = 'X';
                if (board[i][j] == '#') board[i][j] = 'O';
            }
        }
    }
};