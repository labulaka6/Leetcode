static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 二分查找 - 递归
// 将数组一分为二肯定有一个子数组是完全有序的，另一个子数组可能部分有序，也可能完全有序

class Solution {
    int binarySearch(vector<int>& nums, int target, int l, int r){
        if(l > r) return -1;
        if(nums[l] == target || nums[r] == target) return nums[l] == target ? l : r;
        int mid = l + (r-l)/2;
        int ans = -1;
        if(nums[l] > nums[mid]){  // 左边子数组部分有序
            if(target > nums[mid] && target < nums[r]) ans = binarySearch(nums, target, mid+1, r);
            else ans = binarySearch(nums, target, l, mid);
        }else{  // 左边子数组完全有序
            if(target > nums[mid] || target < nums[l]) ans = binarySearch(nums, target, mid+1, r);
            else ans = binarySearch(nums, target, l, mid);
        }
        return ans;
    }
public:
    int search(vector<int>& nums, int target) {
        return binarySearch(nums, target, 0, nums.size()-1);
    }
};

// 二分查找 - 迭代

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = (int)nums.size();
        if (!n) return -1;
        if (n == 1) return nums[0] == target ? 0 : -1;
        int l = 0, r = n - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (nums[mid] == target) return mid;
            if (nums[0] <= nums[mid]) {
                if (nums[0] <= target && target < nums[mid]) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            } else {
                if (nums[mid] < target && target <= nums[n - 1]) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
        }
        return -1;
    }
};

// 极简迭代
// 来自力扣题解
// https://leetcode-cn.com/problems/search-in-rotated-sorted-array/solution/ji-jian-solution-by-lukelee/

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int lo = 0, hi = nums.size() - 1;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if ((nums[0] > target) ^ (nums[0] > nums[mid]) ^ (target > nums[mid]))
                lo = mid + 1;
            else
                hi = mid;
        }
        return lo == hi && nums[lo] == target ? lo : -1;
    }
};