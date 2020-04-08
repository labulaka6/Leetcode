// 偷懒
// 直接调库函数sort()

class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums;
    }
};

// 手撕快排

class Solution {
    void quickSort(vector<int>& a, int l, int r){
        if(l >= r) return;
        int i = l, j = r;
        int key = a[i];
        while(i < j){
            while(i < j && a[j] > key){
                j--;
            }
            if(i < j){
                a[i] = a[j];
                i++;
            }
            while(i < j && a[i] < key){
                i++;
            }
            if(i < j){
                a[j] = a[i];
                j--;
            }
        }
        a[i] = key;
        quickSort(a, l, i-1);
        quickSort(a, i+1, r);
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        quickSort(nums, 0, nums.size()-1);
        return nums;
    }
};

// 手撕堆排序

class Solution {
    void maxHeapify(vector<int>& nums, int i, int len) {  // 大根堆调整过程
        for (; (i << 1) + 1 <= len;) {  // i << 1 就是 i*2
            int lson = (i << 1) + 1;    // 左子结点
            int rson = (i << 1) + 2;    // 右子结点
            int large;
            if (lson <= len && nums[lson] > nums[i]) {  // 左边子结点大于父结点
                large = lson;
            }
            else {
                large = i;
            }
            if (rson <= len && nums[rson] > nums[large]) {  // 右边子结点大于上一步中的较大结点
                large = rson;
            }
            if (large != i) {   // 如果父结点不为最大，父结点与最大的结点互换
                swap(nums[i], nums[large]);
                i = large;
            }
            else break;
        }
    }
    // 另一种更简洁的调整大根堆的方式
    // void maxHeapify(vector<int>& nums, int i, int len) {  // 大根堆调整过程
    //     int j = 2*i + 1; // 左子节点

    //     while(j <= len){
    //         // 在左右子节点中寻找最大的
    //         if(j + 1 <= len && nums[j+1] > nums[j]){
    //             j++;
    //         }

    //         if(nums[i] >= nums[j])
    //             break;

    //         // 较大节点上移
    //         swap(nums[i], nums[j]);

    //         i = j;
    //         j = 2*i + 1;
    //     }
    // }
    void buildMaxHeap(vector<int>& nums, int len) {  // 构建大根堆
        for (int i = len / 2; i >= 0; --i) {
            maxHeapify(nums, i, len);
        }
    }
    void heapSort(vector<int>& nums) {   // 堆排主函数
        int len = nums.size() - 1;
        buildMaxHeap(nums, len);
        for (int i = len; i >= 1; --i) {
            swap(nums[i], nums[0]);
            len -= 1;
            maxHeapify(nums, 0, len);
        }
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        heapSort(nums);
        return nums;
    }
};

// 手撕归并排序

class Solution {
    vector<int> tmp;  // 额外数组
    void mergeSort(vector<int>& nums, int l, int r) {
        if (l >= r) return;
        int mid = (l + r) >> 1;  // (l + r)/2
        mergeSort(nums, l, mid);
        mergeSort(nums, mid + 1, r);
        int i = l, j = mid + 1;
        int cnt = 0;
        while (i <= mid && j <= r) {
            if (nums[i] < nums[j]) {
                tmp[cnt++] = nums[i++];
            }
            else {
                tmp[cnt++] = nums[j++];
            }
        }
        while (i <= mid) tmp[cnt++] = nums[i++];
        while (j <= r) tmp[cnt++] = nums[j++];
        for (int i = 0; i < r - l + 1; ++i) nums[i + l] = tmp[i];
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        tmp.resize((int)nums.size(), 0);  // 分配空间，初始化为0
        mergeSort(nums, 0, (int)nums.size() - 1);
        return nums;
    }
};