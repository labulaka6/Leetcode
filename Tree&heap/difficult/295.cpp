static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 插入排序
// 超出时间限制
// 18 / 18 个通过测试用例

class MedianFinder {
private:
    vector<int> nums;
    int len;
public:
    /** initialize your data structure here. */
    MedianFinder() {
        len = 0;
    }

    void addNum(int num) {
        vector<int>::iterator it;
        for(it = nums.begin(); it != nums.end(); ++it){
            if(num < *it) break;
        }
        nums.insert(it, num);
        len++;
    }

    double findMedian() {
        if(len == 0) return nullptr;
        double ans = 0;
        if(len % 2 == 0) ans = (nums[len/2] + nums[len/2 - 1])/2.0;
        else ans = nums[len/2];
        return ans;
    }
};

// 插入排序改进
// 采用二分查找寻找插入位置

class MedianFinder {
private:
    vector<int> nums;
    int len;
public:
    /** initialize your data structure here. */
    MedianFinder() {
        len = 0;
    }

    void addNum(int num) {
        vector<int>::iterator it;
        it = upper_bound(nums.begin(), nums.end(), num);
        nums.insert(it, num);
        len++;
    }

    double findMedian() {
        if(len == 0) return nullptr;
        double ans = 0;
        if(len % 2 == 0) ans = (nums[len/2] + nums[len/2 - 1])/2.0;
        else ans = nums[len/2];
        return ans;
    }
};

// 两个堆
// 一个大顶堆，一个小顶堆 各存一半数据
// 相当于一个排序后的数组，大顶堆来存前半部分数据，小顶堆来存后半部分数据

class MedianFinder {
    priority_queue<int> lo;                              // 大顶堆
    priority_queue<int, vector<int>, greater<int>> hi;   // 小顶堆

public:
    /** initialize your data structure here. */
    MedianFinder() {

    }

    void addNum(int num) {
        lo.push(num);  // 存入大顶堆

        hi.push(lo.top());  // 前半部分数据的最大值存入小顶堆
        lo.pop();           // 每次都进行这步操作可以保证小顶堆储存的数据都大于大顶堆储存的数据

        if (lo.size() < hi.size()) {  // 保持平衡
            lo.push(hi.top());
            hi.pop();
        }
    }

    double findMedian() {
        return lo.size() > hi.size() ? (double) lo.top() : (lo.top() + hi.top()) * 0.5;
    }
};