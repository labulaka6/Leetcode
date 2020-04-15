// 暴力解法

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        int len = A.size();
        int count = 0;
        for(int i = 0; i < len-2; ++i){
            int d = A[i+1] - A[i];
            for(int j = i+2; j < len; ++j){
                if(d == A[j] - A[j-1]) count++;
                else break;
            }
        }
        return count;
    }
};

// 动态规划
// dp[i]为以i为结尾的等差数列的数目
// 若从l-r为等差数列 则设以r-1为结尾的等差数列个数为x
// 在这x个等差数列结尾加上r则是以r为结尾的等差数列，再加上r-2,r-1,r
// 总数目为x+1
// 所以 dp[i] = dp[i-1] + 1

class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        int len = A.size();
        vector<int> dp (len, 0);
        int sum = 0;
        for (int i = 2; i < len; i++) {
            if (A[i] - A[i - 1] == A[i - 1] - A[i - 2]) {
                dp[i] = 1 + dp[i - 1];
                sum += dp[i];
            }
        }
        return sum;
    }
};

// 递归
// 思想与动态规划一样

class Solution {
    int sum = 0;
    int slices(vector<int>& A, int i) {
        if (i < 2)
            return 0;
        int ap = 0;
        if (A[i] - A[i - 1] == A[i - 1] - A[i - 2]) {
            ap = 1 + slices(A, i - 1);
            sum += ap;
        } else
            slices(A, i - 1);
        return ap;
    }
public:
    int numberOfArithmeticSlices(vector<int>& A) {
        slices(A, A.size() - 1);
        return sum;
    }
};