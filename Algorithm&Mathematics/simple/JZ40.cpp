// 直接调用sort()排好序输出前k个

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        if(arr.size() == 0 || k >= arr.size()) return arr;
        sort(arr.begin(), arr.end());
        vector<int> ans(k, 0);
        for(int i = 0; i < k; ++i){
            ans[i] = arr[i];
        }
        return ans;
    }
};

// 大根堆

class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int>vec(k, 0);
        if (k == 0) return vec; // 排除 0 的情况
        priority_queue<int>Q;
        for (int i = 0; i < k; ++i) Q.push(arr[i]);   // 前k个入堆
        for (int i = k; i < (int)arr.size(); ++i) {   // 第k+1个开始，比堆顶大直接舍弃
            if (Q.top() > arr[i]) {    // 比堆顶小，堆顶弹出，入堆
                Q.pop();
                Q.push(arr[i]);
            }
        }
        for (int i = 0; i < k; ++i) {   // 将堆装入数组
            vec[i] = Q.top();
            Q.pop();
        }
        return vec;
    }
};

// 快排思想

class Solution {
    int partition(vector<int>& nums, int l, int r) {  // 一次快排
        int pivot = nums[r];
        int i = l - 1;
        for(int j = l; j <= r - 1; ++j) {
            if(nums[j] <= pivot) {
                i = i + 1;
                swap(nums[i], nums[j]);
            }
        }
        swap(nums[i + 1], nums[r]);
        return i + 1;
    }
    // 基于随机的划分
    int randomized_partition(vector<int>& nums, int l, int r) {  // 随机选一个数放在nums[r]然后进行一次快排
        int i = rand() % (r - l + 1) + l;
        swap(nums[r], nums[i]);
        return partition(nums, l, r);
    }
    void randomized_selected(vector<int>& arr, int l, int r, int k) {  //
        if(l >= r) return;
        int pos = randomized_partition(arr, l, r);  // 随机划分快排一次
        int num = pos - l + 1;  // 左边区间
        if(k == num) return;
        else if(k < num) randomized_selected(arr, l, pos - 1, k);  // 对左边区间随机划分快排一次
        else randomized_selected(arr, pos + 1, r, k - num);   // 对右边区间随机划分快排一次
    }
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        srand((unsigned)time(NULL));
        randomized_selected(arr, 0, arr.size() - 1, k);
        vector<int> vec;
        for (int i = 0; i < k; ++i) vec.push_back(arr[i]);
        return vec;
    }
};

// 计数排序
// 记录每个数出现的次数，此处就不列举了
// 数字会重复出现可用