
static const auto _ =[](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    void merge(vector<int>& A, int m, vector<int>& B, int n) {  // m为A的实际长度，不包含尾部的0
        for(int i = 0; i < n; ++i){
            A[m + i] = B[i];
        }
        sort(A.begin(), A.end());
    }
};

// 双指针
// 两个数组已经排序好了
// 将两个数组看作队列，每次从两个数组头部取出比较小的数字放到结果中

class Solution {
public:
    void merge(vector<int>& A, int m, vector<int>& B, int n) {
        int pa = 0, pb = 0;
        int sorted[m + n];
        int cur;
        while (pa < m || pb < n) {
            if (pa == m)
                cur = B[pb++];
            else if (pb == n)
                cur = A[pa++];
            else if (A[pa] < B[pb])
                cur = A[pa++];   //pa++ 先使用pa的值再自加1
            else
                cur = B[pb++];
            sorted[pa + pb - 1] = cur;
        }
        for (int i = 0; i != m + n; ++i)
            A[i] = sorted[i];
    }
};

// 反向双指针
// 上面的方法中之所以要使用临时变量，是因为如果直接合并到数组 A 中，A 中的元素可能会在取出之前被覆盖。
// 那么如何直接避免覆盖 A 中的元素呢？观察可知，A 的后半部分是空的，可以直接覆盖而不会影响结果。
// 因此可以指针设置为从后向前遍历，每次取两者之中的较大者放进 A 的最后面。
// 这里推理一下可知：
// A中的原本的数都不会被覆盖

class Solution {
public:
    void merge(vector<int>& A, int m, vector<int>& B, int n) {
        int pa = m - 1, pb = n - 1;
        int tail = m + n - 1;
        int cur;
        while (pa >= 0 || pb >= 0) {
            if (pa == -1)
                cur = B[pb--];
            else if (pb == -1)
                cur = A[pa--];
            else if (A[pa] > B[pb])
                cur = A[pa--];
            else
                cur = B[pb--];
            A[tail--] = cur;
        }
    }
};
