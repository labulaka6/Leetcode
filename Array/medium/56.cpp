// 排序后合并

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
    void quickSort(vector<vector<int>>& a, int l, int r){
        if(l >= r) return;
        int i = l, j = r;
        int key = a[i][0], tem = a[i][1];
        while(i < j){
            while(i < j && a[j][0] > key){
                j--;
            }
            if(i < j){
                a[i][0] = a[j][0];
                a[i][1] = a[j][1];
                i++;
            }
            while(i < j && a[i][0] < key){
                i++;
            }
            if(i < j){
                a[j][0] = a[i][0];
                a[j][1] = a[i][1];
                j--;
            }
        }
        a[i][0] = key;
        a[i][1] = tem;
        quickSort(a, l, i-1);
        quickSort(a, i+1, r);
    }
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int len = intervals.size();
        if(len < 2) return intervals;
        quickSort(intervals, 0, len-1);
        vector<vector<int>> ans;
        ans.emplace_back(intervals[0]);  // emplace_back 效率相对比push_back更高
        for(int i = 1; i < len; ++i){
            while(intervals[i][0] <= ans.back()[1]){
                if(intervals[i][1] > ans.back()[1]) ans.back()[1] = intervals[i][1];
                ++i;
                if(i == len) return ans;
            }
            ans.emplace_back(intervals[i]);
        }
        // 另一种合并方式,更好理解一些
        // int i = 0;
        // while (i < len) {
        //     int left = intervals[i][0];
        //     int right = intervals[i][1];
        //     while (i < len - 1 && intervals[i + 1][0] <= right) {
        //         i++;
        //         right = max(right, intervals[i][1]);
        //     }
        //     ans.emplace_back(vector<int> {left, right});
        //     i++;
        // }
        return ans;
    }
};


// 可以直接使用库函数进行排序

class Solution {
public:
    // 1. 排序
    // 2. 插入第0个intervals
    // 3. 从第一个开始依次检查 intervals[i][0]与 res.back()[1]
    //    小于等于 需要合并 改变res back [1] 为二者 [1] 的较大值
    //    大于  不需要合并 直接插入
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if(intervals.size() < 2) return intervals;
        vector<vector<int>> res;
        sort(intervals.begin(), intervals.end(),
                [](const vector<int>& x, const vector<int>& y){
                    return x[0] < y[0];
                });  // 这里也可以不自定义排序规则，但是执行速度会下降
        res.emplace_back(intervals[0]);  // emplace_back 效率相对比push_back更高
        for(int i = 1; i < intervals.size(); ++i){
            while(intervals[i][0] <= res.back()[1]){
                if(intervals[i][1] > res.back()[1]) res.back()[1] = intervals[i][1];
                ++i;
                if(i == intervals.size()) return res;
            }
            res.emplace_back(intervals[i]);
        }
        return res;
    }
};