static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 暴力优化

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        int len = nums.size();
        if (len == 0) return res;

        // maxInd记录每次最大值的下标，maxi记录最大值
        int maxInd = -1, maxi = INT_MAX;

        for (int i = 0; i < len - k + 1; ++i) {
            // 判断最大值下标是否在滑动窗口的范围内
            if (maxInd >= i){
                // 存在就只需要比较最后面的值是否大于上一个窗口最大值
                if (nums[i + k - 1] > maxi){
                    maxi = nums[i + k - 1];
                    // 更新最大值下标
                    maxInd = i + k - 1;
                }
            }
            // 如果不在就重新寻找当前窗口最大值
            else {
                maxi = nums[i];
                for (int j = i; j < i + k; ++j) {
                    if (maxi < nums[j]) {
                        maxi = nums[j];
                        maxInd = j;
                    }
                }
            }
            res.emplace_back(maxi);
        }
        return res;
    }
};

// 优先队列

class MonotonicQueue {
private:
    deque<int> data;
public:
    void push(int n) {
        while (!data.empty() && data.back() < n) 
            data.pop_back();
        data.push_back(n);
    }

    int max() { return data.front(); }

    void pop(int n) {
        if (!data.empty() && data.front() == n)
            data.pop_front();
    }
};

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        MonotonicQueue window;
        vector<int> res;
        for (int i = 0; i < nums.size(); i++) {
            if (i < k - 1) {  // 先填满窗口的前 k - 1
                window.push(nums[i]);
            } else {  // 窗口向后滑动
                window.push(nums[i]);
                res.push_back(window.max());
                window.pop(nums[i - k + 1]);
            }
        }
        return res;
    }
};

// 动态规划
// 将整个数组都分割为具有k个元素的块
// 滑动窗口可能在一个块内，也可能在两个块内
// 建立两个数组，一个从左向右遍历记录块内已遍历过的最大值，一个从右向左遍历记录块内已遍历过的最大值
// 设窗口为[i, j] 则滑动窗口内的最大值为 max(right[i], left[j])

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        int n = nums.size();
        if (n == 0 || k == 0) return res;
        if (k == 1) return nums;

        vector<int> left(n);
        left[0] = nums[0];
        vector<int> right(n);
        right[n - 1] = nums[n - 1];
        for (int i = 1; i < n; i++) {
            // 从左到右
            if (i % k == 0) left[i] = nums[i];  // 块开始位置
            else left[i] = max(left[i - 1], nums[i]);

            // 从右到左
            int j = n - i - 1;
            if ((j + 1) % k == 0) right[j] = nums[j];  // 块结束位置
            else right[j] = max(right[j + 1], nums[j]);
        }

        for (int i = 0; i < n - k + 1; i++){
            res.emplace_back(max(left[i + k - 1], right[i]));
        }

        return res;
    }
};