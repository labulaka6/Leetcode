// 动态规划
// dp[i][j]表示到(i,j)位置的下降路径最小和
// 直接在原数组操作

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& A) {
        int m = A.size();
        int n = A[0].size();
        for(int i = 1; i < m; ++i){
            for(int j = 0; j < n; ++j){
                if(j == 0){
                    A[i][j] = min(A[i-1][j], A[i-1][j+1]) + A[i][j];
                }else if(j == n-1){
                    A[i][j] = min(A[i-1][j-1], A[i-1][j]) + A[i][j];
                }else{
                    A[i][j] = min(min(A[i-1][j-1], A[i-1][j]), A[i-1][j+1]) + A[i][j];
                }
            }
        }
        int min = A[m-1][0];
        for(int i = 1; i < n; ++i){
            if(A[m-1][i] < min) min = A[m-1][i];
        }

        return min;
    }
};