static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 1. 暴力：直接遍历
// 2. 两次二分
// 3. 线性查找：利用矩阵的性质从右上角或者左下角开始查找(此处为右上角)

class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        if (matrix.size() == 0 || matrix[0].size() == 0) return false;
        int rows = matrix.size(), columns = matrix[0].size();
        int row = 0, column = columns - 1;
        while (row < rows && column >= 0) {
            int num = matrix[row][column];
            if (num == target) return true;
            else if (num > target) column--;
            else row++;
        }
        return false;
    }
};