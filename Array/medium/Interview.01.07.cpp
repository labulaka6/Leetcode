// 直观解法
// 找出规律：matrix[i][j]旋转后位置为matrix[j][m-1-i]
// 需要额外空间

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int tem[n][n];
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                tem[j][n-1-i] = matrix[i][j];
            }
        }
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                matrix[i][j] = tem[i][j];
            }
        }
    }
};

// 改进
// 取一个临时变量来完成原地旋转

// 当 n 为偶数时，需要枚举 n^2 / 4 = (n/2)*(n/2) 个位置，矩阵的左上角符合要求。
// 例如 n = 4
// **..  ..**  ....  ....
// **..  ..**  ....  ....
// ....  ....  ..**  **..
// ....  ....  ..**  **..
// 保证了不重复、不遗漏

// 当 n 为奇数时，由于中心的位置经过旋转后位置不变，需要枚举 (n^2-1) / 4 = ((n-1)/2) * ((n+1)/2) 个位置，
// 同样可以使用矩阵左上角对应大小的子矩阵。
// 例如 n = 5
// ***..  ...**  .....  .....
// ***..  ...**  .....  .....
// .....  ...**  .....  **...
// .....  .....  ..***  **...
// .....  .....  ..***  **...
// 同样保证了不重复、不遗漏

// 综上所述，只需要枚举矩阵左上角高为 ⌊n/2⌋，宽为 ⌊(n+1)/2⌋ 的子矩阵即可。

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for (int i = 0; i < n / 2; ++i) {
            for (int j = 0; j < (n + 1) / 2; ++j) {  // 旋转后四个相对位置的元素依次换位
                int temp = matrix[i][j];
                matrix[i][j] = matrix[n - j - 1][i];
                matrix[n - j - 1][i] = matrix[n - i - 1][n - j - 1];
                matrix[n - i - 1][n - j - 1] = matrix[j][n - i - 1];
                matrix[j][n - i - 1] = temp;
            }
        }
    }
};

// 两次反转
// 水平反转然后主对角线反转即可

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        // 水平翻转
        for (int i = 0; i < n / 2; ++i) {
            for (int j = 0; j < n; ++j) {
                swap(matrix[i][j], matrix[n - i - 1][j]);
            }
        }
        // 主对角线翻转
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
    }
};