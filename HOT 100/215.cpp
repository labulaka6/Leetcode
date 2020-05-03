static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 排序

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int ans = nums[nums.size()-k];
        return ans;
    }
};

// 小根堆

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        // 小根堆
        priority_queue<int, vector<int>, greater<int>> Q;
        // 在堆中保留k个最大的元素
        for (int n: nums) {
            Q.push(n);
            if (Q.size() > k)
                Q.pop();
        }
        return Q.top();
    }
};

// 快速选择算法

class Solution {
    int partition(vector<int>& nums, int left, int right, int pivot_index) {
        int pivot = nums[pivot_index];
        // 1. 将枢轴移动到末端
        swap(nums[pivot_index], nums[right]);
        int store_index = left;
        // 2. 将所有小的元素移到左边
        for (int i = left; i <= right; i++) {
            if (nums[i] < pivot) {
                swap(nums[store_index], nums[i]);
                store_index++;
            }
        }
        // 3. 将枢轴移动到它的最终位置
        swap(nums[store_index], nums[right]);
        return store_index;
    }

    int quickselect(vector<int>& nums, int left, int right, int k_smallest) {  // 返回列表中第k小的元素
        if (left == right) // 只有一个元素
        return nums[left];  // 返回这个元素
        // 选择一个随机的pivot_index
        srand(time(0));
        int pivot_index = left + (rand() % (right - left));
        pivot_index = partition(nums, left, right, pivot_index);
        // 枢轴在(N - k)位置上
        if (k_smallest == pivot_index) return nums[k_smallest];
        // 在左边寻找
        else if (k_smallest < pivot_index) return quickselect(nums, left, pivot_index - 1, k_smallest);
        // 在右边寻找
        return quickselect(nums, pivot_index + 1, right, k_smallest);
    }

public:
    int findKthLargest(vector<int>& nums, int k) {
        int size = nums.size();
        // 第k大的位置是(N - k)
        return quickselect(nums, 0, size - 1, size - k);
    }
};