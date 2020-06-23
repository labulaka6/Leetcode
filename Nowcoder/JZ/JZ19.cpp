static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 设矩阵 左、右、上、下 四个边界 l , r , t , b

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if(matrix.size() == 0) return {};
        int l = 0, r = matrix[0].size() - 1, t = 0, b = matrix.size() - 1, x = 0;
        vector<int> res((r + 1) * (b + 1));
        while(true) {
            for(int i = l; i <= r; ++i) res[x++] = matrix[t][i]; // left to right.
            if(++t > b) break;
            for(int i = t; i <= b; ++i) res[x++] = matrix[i][r]; // top to bottom.
            if(l > --r) break;
            for(int i = r; i >= l; --i) res[x++] = matrix[b][i]; // right to left.
            if(t > --b) break;
            for(int i = b; i >= t; --i) res[x++] = matrix[i][l]; // bottom to top.
            if(++l > r) break;
        }
        return res;
    }
};

// 另外从题解看到了一个有意思的Python解法
// 解题思路：将矩阵第一行的元素添加到res列表里，删除第一行（也就是matrix中的第一个列表），
// 然后逆时针旋转（这里通过转置+倒序实现），新的matrix的第一行即为接下来要打印的元素。

// class Solution:
//     def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
//         res = []
//         while matrix:
//             res += matrix.pop(0)  // 记录并删除第一行
//             matrix = list(zip(*matrix))[::-1]  // 转置矩阵，然后以行为单位翻转
//         return res