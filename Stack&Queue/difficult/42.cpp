// 个人想法
// 其实只要找到最高的那根柱子就很容易计算了
// 任意一根柱子与最高柱子之间的水面高度不会低于这个柱子的高度
// 如果这根柱子与最高柱子之间的其他柱子比这根柱子低，水面高度就等于这跟柱子的高度
// 如果这根柱子x与最高柱子y之间的其他柱子z比这根柱子高，
// 则x-z之间的水面高度为x的高度，z-y之间的水面高度为z的高度
// 总而言之，水面的高度取决于两边柱子中较低的那一根

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int trap(vector<int>& height) {
        int len = height.size();
        if(len == 0) return 0;
        int water = 0, pillar = 0;  // 记录水量与柱子所占的位置
        int high = 0, location = 0;  // 记录最高柱子的高度与位置
        for(int i = 0; i < len; ++i){  // 寻找最高柱子的位置
            if(high < height[i]){
                high = height[i];
                location = i;
            }
        }
        for(int i = 0; i <= location; ++i){  // 最高柱子左边的水量
            if(pillar < height[i]){
                pillar = height[i];
            }else{
                water = water + pillar - height[i];  // 水面高度 - 柱子高度 = 水量
            }
        }
        pillar = 0;
        for(int i = len - 1; i >= location; --i){  // 最高柱子右边的水量
            if(pillar < height[i]){
                pillar = height[i];
            }else{
                water = water + pillar - height[i];
            }
        }
        return water;
    }
};

// 直观解法
// 对于数组中的每个元素，找出下雨后水能达到的最高位置，等于两边最大高度的较小值减去当前高度的值。

class Solution {
public:
    int trap(vector<int>& height){
        int ans = 0;
        int size = height.size();
        for (int i = 1; i < size - 1; i++) {
            int max_left = 0, max_right = 0;
            for (int j = i; j >= 0; j--) { // 当前位置左边的最大值
                max_left = max(max_left, height[j]);
            }
            for (int j = i; j < size; j++) { // 当前元素右边的最大值
                max_right = max(max_right, height[j]);
            }
            ans += min(max_left, max_right) - height[i];  // 当前位置雨水量
        }
        return ans;
    }
};

// 直观解法改进
// 在直观解法中，仅仅为了找到最大值每次都要向左和向右扫描一次。
// 但是可以提前存储这个值。因此，可以通过动态编程解决。

class Solution {
public:
    int trap(vector<int>& height){
        if(height == null)
            return 0;
        int ans = 0;
        int size = height.size();
        vector<int> left_max(size), right_max(size);
        left_max[0] = height[0];
        for (int i = 1; i < size; i++) {  // 从左向右扫描
            left_max[i] = max(height[i], left_max[i - 1]);
        }
        right_max[size - 1] = height[size - 1];
        for (int i = size - 2; i >= 0; i--) {  // 从右向左扫描
            right_max[i] = max(height[i], right_max[i + 1]);
        }
        for (int i = 1; i < size - 1; i++) {  // 计算水量
            ans += min(left_max[i], right_max[i]) - height[i];
        }
        return ans;
    }
};

// 栈
// 在遍历数组时维护一个栈。
// 如果当前的条形块小于或等于栈顶的条形块，将条形块的索引入栈，
// 意思是当前的条形块被栈中的前一个条形块界定。
// 如果发现一个条形块长于栈顶，可以确定栈顶的条形块被当前条形块和栈的前一个条形块界定，
// 因此我们可以弹出栈顶元素并且累加答案到 \text{ans}ans 。

class Solution {
public:
    int trap(vector<int>& height){
        int ans = 0, current = 0;
        stack<int> st;
        while (current < height.size()) {
            // 栈非空且height[current] > height[st.top()]
            while (!st.empty() && height[current] > height[st.top()]) {
                int top = st.top();
                st.pop();
                if (st.empty())
                    break;
                int distance = current - st.top() - 1;  // 计算当前元素和栈顶元素的距离，准备进行填充操作
                // 找出界定高度
                int bounded_height = min(height[current], height[st.top()]) - height[top];
                ans += distance * bounded_height;  // 往答案中累加积水量
            }
            st.push(current++);  // 将当前索引下标入栈，将current移动到下个位置
        }
        return ans;
    }
};

// 双指针法

// left_max：左边的最大值，它是从左往右遍历找到的
// right_max：右边的最大值，它是从右往左遍历找到的
// left：从左往右处理的当前下标
// right：从右往左处理的当前下标

// 在某个位置i处，它能存的水，取决于它左右两边的最大值中较小的一个。
// 当从左往右处理到left下标时，左边的最大值left_max对它而言是可信的，但right_max对它而言是不可信的。
// 当从右往左处理到right下标时，右边的最大值right_max对它而言是可信的，但left_max对它而言是不可信的。
// 对于位置left而言，它左边最大值一定是left_max，右边最大值“大于等于”right_max，
// 这时候，如果left_max<right_max成立，那么它就知道自己能存多少水了。
// 无论右边将来会不会出现更大的right_max，都不影响这个结果。
// 所以当left_max<right_max时，处理left下标，反之，处理right下标。

class Solution {
public:
    int trap(vector<int>& height){
        int left = 0, right = height.size() - 1;
        int ans = 0;
        int left_max = 0, right_max = 0;  // 从左到右方向的最大值与从右到左方向的最大值
        while (left < right) {
            // 另一种写法
            // 可以认为如果一端有更高的条形块（例如右端），积水的高度依赖于当前方向的高度（从左到右）。
            // 当发现另一侧（右侧）的条形块高度不是最高的，则开始从相反的方向遍历（从右到左）。
            // 必须在遍历时维护 left_max 和 right_max ，但是可以使用两个指针交替进行，实现 1 次遍历即可完成。
            
            // if (height[left] < height[right]) {
            //     height[left] >= left_max ? (left_max = height[left]) : ans += (left_max - height[left]);
            //     ++left;
            // }
            // else {
            //     height[right] >= right_max ? (right_max = height[right]) : ans += (right_max - height[right]);
            //     --right;
            // }
            if(left_max<right_max){
                ans += max(0, left_max - height[left]);
                left_max = max(left_max, height[left]);
                left++;
            }else{
                ans += max(0, right_max - height[right]);
                right_max = max(right_max, height[right]);
                right--;
            }
        }
        return ans;
    }
};