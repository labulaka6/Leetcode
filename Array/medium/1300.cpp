static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 二分查找

class Solution {
private:
    int calculateSum(vector<int>& arr, int threshold) {  // 求改变后的数组之和
        int sum = 0;
        for (int num : arr) {
            sum += min(num, threshold);
        }
        return sum;
    }

public:
    int findBestValue(vector<int> arr, int target) {
        int left = 0;
        int right = 0;
        int n = arr.size();

        for (int num : arr) {
            right = max(right, num);
        }

        while (left < right) {
            int mid = left + (right - left + 1) / 2;
            int sum = calculateSum(arr, mid);
            // 计算最后 1 个使得转变以后数组的和小于等于 target 的阈值 threshold
            if (sum > target) {
                // 大于等于的就不是解，threshold 太大了，下一轮搜索区间是 [left, mid - 1]
                right = mid - 1;
            } else {
                // 下一轮搜索区间是 [mid, right]
                left = mid;
            }
        }

        // 比较阈值线分别定在 left 和 left + 1 的时候与 target 的接近程度
        int sum1 = calculateSum(arr, left);
        int sum2 = calculateSum(arr, left + 1);
        // 注意：这里必须加绝对值，因为有可能出现 sum1 == sum2 < target 的情况
        if (abs(target - sum1) <= abs(sum2 - target)) {
            return left;
        }
        return left + 1;
    }
};

// 两次二分

class Solution {
public:
    int check(const vector<int>& arr, int x) {  // 计算和
        int ret = 0;
        for (const int& num: arr) {
            ret += (num >= x ? x : num);
        }
        return ret;
    }

    int findBestValue(vector<int>& arr, int target) {
        sort(arr.begin(), arr.end());
        int n = arr.size();
        vector<int> prefix(n + 1);  // 前缀和数组
        for (int i = 1; i <= n; ++i) {
            prefix[i] = prefix[i - 1] + arr[i - 1];
        }

        int l = 0, r = arr[n-1], ans = -1;
        while (l <= r) {
            int mid = (l + r) / 2;
            auto iter = lower_bound(arr.begin(), arr.end(), mid);  // 在arr中找到第一个大于等于mid的值
            int cur = prefix[iter - arr.begin()] + (arr.end() - iter) * mid;  // 改变后的数组之和
            // 寻找最后一个使得cur小于等于target的数
            if (cur <= target) {
                ans = mid;
                l = mid + 1;
            }else {
                r = mid - 1;
            }
        }
        // 答案为ans与ans+1中使得cur与target差值的绝对值最小的那个
        int choose_small = check(arr, ans);
        int choose_big = check(arr, ans + 1);
        return abs(choose_small - target) <= abs(choose_big - target) ? ans : ans + 1;
    }
};