static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 插入排序 - 超出时间限制

class Solution {
public:
    int reversePairs(vector<int>& nums) {
        int ans = 0, count = 0;
        for(int i = 1, i < nums.size(); ++i){
            count = 0;
            int j = i; tem = nums[i];
            while(j > 0 && tem < nums[j-1]){
                    count++;
                    nums[j] = nums[j-1];
            }
            nums[j] = tem;
            ans += count;
        }
        return ans;
    }
};

// 归并排序

class Solution {
public:
    int mergeSort(vector<int>& nums, vector<int>& tmp, int l, int r) {
        if (l >= r) {
            return 0;
        }

        int mid = l + (r-l)/2;  // 取分治点 防止l与r过大发生整型溢出
        // 左区间与右区间的逆序对
        int inv_count = mergeSort(nums, tmp, l, mid) + mergeSort(nums, tmp, mid + 1, r);
        int i = l, j = mid + 1, pos = l;
        while (i <= mid && j <= r) {
            if (nums[i] <= nums[j]) {  // 左区间当前元素小于等于右区间当前元素
                tmp[pos] = nums[i];
                ++i;
            }else { // 右区间当前元素小于等于左区间当前元素，因为两个区间均有序，所以与左区间所有元素均构成逆序对
                tmp[pos] = nums[j];
                inv_count += mid - i + 1;
                ++j;
            }
            ++pos;
        }
        for (int k = i; k <= mid; ++k) {
            tmp[pos++] = nums[k];
        }
        for (int k = j; k <= r; ++k) {
            tmp[pos++] = nums[k];
        }
        // 将排好序的区间放回去
        copy(tmp.begin() + l, tmp.begin() + r + 1, nums.begin() + l);
        return inv_count;
    }

    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        vector<int> tmp(n);
        return mergeSort(nums, tmp, 0, n - 1);
    }
};