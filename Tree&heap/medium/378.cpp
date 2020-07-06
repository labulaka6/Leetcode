static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 大根堆

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        priority_queue<int> pq;
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                pq.push(matrix[i][j]);
                if (pq.size() > k) pq.pop();
            }
        }
        return pq.top();
    }
};

// 二分查找
// 矩阵最左上角为最小值，最右下角为最大值，在此范围内进行二分搜索，取中间数mid，然后在每行中查找mid，
// 这里使用upper_bound，在每行查找第一个大于mid的元素，如果目标数比该行的尾元素大，则upper_bound返回该行元素个数，
// 如果目标数比该行第一个元素小，则uppper_bound返回0，遍历完所有行可以确定mid是第几小的数，
// 然后与k进行比较，进行二分查找，left和right最终相等，会变为数组中第k小的数。
// 整体时间复杂度为 O(nlgn*lgX)，X为最大值与最小值的差值

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int left = matrix[0][0], right = matrix.back().back();
        while (left < right) {
            int mid = left + (right - left) / 2, cnt = 0;
            for (int i = 0; i < matrix.size(); ++i) {
                cnt += upper_bound(matrix[i].begin(), matrix[i].end(), mid) - matrix[i].begin();
            }
            if (cnt < k) left = mid + 1;
            else right = mid;
        }
        return left;
    }
};

// 二分查找优化
// 时间复杂度为O(nlgX)，X为最大值与最小值的差值

class Solution {
private:
    int search_less_equal(vector<vector<int>> &matrix, int target) {
        // 以列为单位找，找到每一列最后一个<=mid的数即知道每一列有多少个数<=mid
        int n = matrix.size(), i = n - 1, j = 0, res = 0;
        while (i >= 0 && j < n) {
            if (matrix[i][j] <= target) {
                // 第j列有i+1个元素<=mid
                res += i + 1;
                ++j;
            } else {
                // 第j列目前的数大于mid，需要继续在当前列往上找
                --i;
            }
        }
        return res;
    }

public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int left = matrix[0][0], right = matrix.back().back();
        while (left < right) {
            // 每次循环都保证第K小的数在start~end之间，当start==end，第k小的数就是start
            int mid = left + (right - left) / 2;
            // 找二维矩阵中<=mid的元素总个数
            int cnt = search_less_equal(matrix, mid);
            // 第k小的数在右半部分，且不包含mid
            if (cnt < k) left = mid + 1;
            // 第k小的数在左半部分，可能包含mid
            else right = mid;
        }
        return left;
    }
};