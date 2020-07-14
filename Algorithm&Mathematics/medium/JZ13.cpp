static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 广度优先搜索

class Solution {
    int sum(int n){
        int ans = 0;
        while(n != 0){
            ans += n%10;
            n /= 10;
        }
        return ans;
    }
public:
    int movingCount(int m, int n, int k) {
        queue<pair<int, int>> Q;
        vector<vector<int>> vis(m, vector<int>(n, 0));
        int v1[2] = {1, 0};
        int v2[2] = {0, 1};
        Q.push(pair<int, int> {0, 0});
        vis[0][0] = 1;
        int count = 1;
        while(!Q.empty()){
            int i = Q.front().first;
            int j = Q.front().second;
            Q.pop();
            for(int z = 0; z < 2; ++z){
                int x = i + v1[z];
                int y = j + v2[z];
                if(x < 0 || x >= m || y < 0 || y >= n || vis[x][y]  || sum(x) + sum(y) > k) continue;
                vis[x][y] = 1;
                Q.push(pair<int, int> {x, y});
                count++;
            }
        }
        return count;
    }
};

// 递推

class Solution {
    int get(int x) {
        int res=0;
        for (; x; x /= 10){
            res += x % 10;
        }
        return res;
    }
public:
    int movingCount(int m, int n, int k) {
        if (!k) return 1;
        vector<vector<int>> vis(m, vector<int>(n, 0));
        int ans = 1;
        vis[0][0] = 1;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((i == 0 && j == 0) || get(i) + get(j) > k) continue;
                // 边界判断 及 查看是否可达
                if (i - 1 >= 0) vis[i][j] |= vis[i - 1][j];
                if (j - 1 >= 0) vis[i][j] |= vis[i][j - 1];
                ans += vis[i][j];
            }
        }
        return ans;
    }
};