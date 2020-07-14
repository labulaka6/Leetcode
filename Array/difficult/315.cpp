static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 归并排序 + 索引数组

class Solution {
public:
    vector<int> res;

    vector<int> countSmaller(vector<int>& vec) {

        if (vec.empty()) return {};

        vector<pair<int, int>> nums;  // 索引数组 记录当前操作的数及对应的原始数组的下标
        for (int i = 0; i < vec.size(); ++i){
            nums.emplace_back(vec[i], i);
        }

        res = vector<int> (vec.size(), 0);
        merge_sort(nums, 0, (int)nums.size() - 1);  // 传入索引数组进行归并排序

        return res;
    }

    void merge_sort(vector<pair<int, int>>& nums, int left, int right){
        if (left < right){
            int mid = left + (right - left) / 2;

            merge_sort(nums, left, mid);  // 归并
            merge_sort(nums, mid + 1, right);  // 归并
            merge(nums, left, mid, right);
        }
    }

    void merge(vector<pair<int, int>>& nums, int left, int mid, int right){  // 排序 + 计算[逆序对]
        int i = left, j = mid + 1;
        int k = left;

        vector<pair<int, int>> sort_nums;

        // 前后区间均有序，归并
        while (i <= mid && j <= right){
            if (nums[i].first <= nums[j].first){  // 前区间中当前元素小于后区间中当前元素
                res[nums[i].second] += j - mid - 1;
                sort_nums.push_back(nums[i++]);
            }else if (nums[i].first > nums[j].first){  // 后区间中当前元素小于前区间中当前元素
                sort_nums.push_back(nums[j++]);
            }
        }

        while (i <= mid){
            res[nums[i].second] += j - mid - 1;
            sort_nums.push_back(nums[i++]);
        }

        while (j <= right){
            sort_nums.push_back(nums[j++]);
        }

        for (int m = 0, n = left; m < sort_nums.size(); m++, n++){
            nums[n] = sort_nums[m];
        }
    }
};