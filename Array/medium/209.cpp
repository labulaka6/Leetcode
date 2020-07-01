static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 暴力解法

class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int m = INT_MAX;  // min
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            int start = i;
            int sum = 0;
            while (start < n) {
                sum += nums[start];
                start++;
                // 当前和大于等于 s 的时候结束
                if (sum >= s) {
                    m = min(m, start - i);
                    break;
                }
            }
        }
        //min 是否更新，如果没有更新说明数组所有的数字和小于 s, 没有满足条件的解, 返回 0
        return m == INT_MAX ? 0 : m;
    }
};

// 滑动窗口

class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int len = nums.size();
        if(len == 0) return 0;
        int l = 0, r = 0, sum = 0, m = INT_MAX;
        while(r < nums.size()){
            sum += nums[r];
            r++;
            while(sum >= s){
                m = min(m, r - l);
                sum -= nums[l];
                l++;
            }
        }
        return m == INT_MAX ? 0 : m;
    }
};

// 二分查找

class Solution {
    int binarySearch(int start, int end, vector<int>& sums, int target) {
        int mid = -1;
        while (start <= end) {
            mid = (start + end) >> 1;
            if (sums[mid] == target) {
                return mid;
            } else if (sums[mid] < target) {
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        }
        //是否找到，没有找到返回 -1
        return sums[mid] > target ? mid : -1;
    }

public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        vector<int> sums(n, 0);  // sums为数组前缀和(0-i项之和)
        sums[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            sums[i] = nums[i] + sums[i - 1];
        }
        int m = INT_MAX;
        // for (int i = 0; i < n; i++) {
        //     int s2 = s - nums[i]; // 除去当前数字
        //     for (int j = i; j < n; j++) {
        //         // i + 1 到  j 的所有数字和
        //         if (sums[j] - sums[i] >= s2) {
        //             m = min(m, j - i + 1);
        //         }
        //     }
        // }
        for (int i = 0; i < n; ++i) {
            int s2 = s - nums[i];
            // 二分查找，目标值是 s2 + sums[i]
            // sums[j] - sums[i] >= s2 移项即为 sums[j] >= sums[i] + s2
            int k = binarySearch(i, n - 1, sums, s2 + sums[i]);
            if (k != -1) {
                m = min(m, k - i + 1);
            }

        }
        return m == INT_MAX ? 0 : m;
    }
};