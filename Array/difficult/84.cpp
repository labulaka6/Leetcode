static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 暴力解法
// 依次遍历柱形的高度，对于每一个高度分别向两边扩散，求出以当前高度为矩形的最大宽度多少。
// 超出时间限制， 95 / 96 个通过测试用例

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int len = heights.size();
        int ans = 0;
        for(int i = 0; i < len; ++i){
            int l = 0, r = 0;
            int j = i - 1;
            while(j >= 0 && heights[j] >= heights[i]){
                l++;
                j--;
            }
            j = i + 1;
            while(j < len && heights[j] >= heights[i]){
                r++;
                j++;
            }
            ans = max(ans, heights[i]*(l+r+1));
        }
        return ans;
    }
};

// 单调栈

class Solution {
public:
    int largestRectangleArea(vector<int> &heights) {
        unsigned long size = heights.size();
        if (size == 1) return heights[0];
        int res = 0;
        stack<int> stk;  // 单调栈
        for (int i = 0; i < size; ++i) {  // 遍历数组一遍
            // 栈中有元素且当前元素小于栈顶元素(栈为单调非递减栈)，则栈顶元素高度为高的矩形面积可以确定
            // 虽然栈顶元素可能与次栈顶元素高度相同，导致计算这一个矩形的面积出现误差，但是不会影响最终结果
            // 因为在计算次栈顶元素高度的矩形面积时就相当于计算了栈顶元素高度的矩形的面积
            while (!stk.empty() && heights[stk.top()] > heights[i]) {
                int length = heights[stk.top()];  // 高度
                stk.pop();
                int weight = i;  // 栈为空时的宽度
                if (!stk.empty()) {  // 栈不为空时的宽度
                    weight = i - stk.top() - 1;
                }
                res = max(res, length * weight);  // 取最大面积
            }
            stk.push(i);  // 栈顶元素小于等于当前元素，入栈
        }
        while (!stk.empty()) {  // 所有元素均遍历过，但是栈还不为空(有的以元素为高度的矩形面积还未计算)
            int length = heights[stk.top()];  // 高度为栈顶元素高度
            stk.pop();
            int weight = size;  // 栈为空时宽度为数组宽度
            if (!stk.empty()) {  // 栈不为空时的宽度
                weight = size - stk.top() - 1;
            }
            res = max(res, length * weight);  // 取最大面积
        }
        return res;
    }
};

// 加入哨兵，优化上述代码

class Solution {
public:
    int largestRectangleArea(vector<int> &heights) {
        // 加入哨兵，简化代码，避免特殊情况的讨论，减少判断
        heights.insert(heights.begin(), 0);
        heights.push_back(0);
        unsigned long size = heights.size();
        if(size == 2) return 0;
        if(size == 3) return heights[1];
        int res = 0;
        stack<int> stk;  // 单调栈
        for (int i = 0; i < size; ++i) {  // 遍历数组一遍
            // 栈中有元素且当前元素小于栈顶元素(栈为单调非递减栈)，则栈顶元素高度为高的矩形面积可以确定
            // 虽然栈顶元素可能与次栈顶元素高度相同，导致计算这一个矩形的面积出现误差，但是不会影响最终结果
            // 因为在计算次栈顶元素高度的矩形面积时就相当于计算了栈顶元素高度的矩形的面积
            while (!stk.empty() && heights[stk.top()] > heights[i]) {
                int length = heights[stk.top()];  // 高度
                stk.pop();
                int weight = i - stk.top() - 1;  // 宽度
                res = max(res, length * weight);  // 取最大面积
            }
            stk.push(i);  // 栈顶元素小于等于当前元素，入栈
        }
        return res;
    }
};