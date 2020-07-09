static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 暴力法
// 超出时间限制  43 / 44 个通过测试用例

class Solution {
public:
    vector<int> constructArr(vector<int>& a) {
        vector<int> b;
        for(int i = 0; i < a.size(); ++i){
            int tmp = 1;
            for(int j = 0; j < a.size(); ++j){
                if(j == i) continue;
                tmp *= a[j];
            }
            b.emplace_back(tmp);
        }
        return b;
    }
};

// 对称遍历
// B[i] 就是 A[i] 左边所有元素的积 乘 A[i] 右边所有元素的积。

class Solution {
public:
    vector<int> constructArr(vector<int>& a) {
        vector<int> b;
        if(a.size() == 0) return b;
        b.resize(a.size());
        b[0] = 1;
        int tmp = 1;
        for(int i = 1; i < a.size(); ++i) {
            b[i] = b[i - 1] * a[i - 1];  // 左边
        }
        for(int i = a.size() - 2; i >= 0; --i) {
            tmp *= a[i + 1];  // 右边
            b[i] *= tmp;  // 结果
        }
        return b;
    }
};