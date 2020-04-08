// 数组计数
// 当找到一个没有出现过的数的时候，将之前某个重复出现的数增加成这个没有出现过的数。
// 注意，这里 「之前某个重复出现的数」 是可以任意选择的，它并不会影响最终的答案，
// 因为将 P 增加到 X 并且将 Q 增加到 Y，与将 P 增加到 Y 并且将 Q 增加到 X 都需要进行 (X + Y) - (P + Q) 次操作。

// 例如当数组 A 为 [1, 1, 1, 1, 3, 5] 时，有 3 个重复的 1，且没有出现过 2，4 和 6，
// 因此一共需要进行 (2 + 4 + 6) - (1 + 1 + 1) = 9 次操作。

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int minIncrementForUnique(vector<int>& A) {
        int cnt[80000] = { 0 };
        for (int x: A) cnt[x]++;  // 计数

        int ans = 0, taken = 0;

        for (int x = 0; x < 80000; ++x) {  // 遍历
            if (cnt[x] >= 2) {  // 数量大于2个
                taken += cnt[x] - 1;  // 需要改动的数的数量(重复的数量-1)
                ans -= x * (cnt[x] - 1);  // 解释如题前注释，这里是为了计算P+Q 即减去(重复出现的数相加之和)
            }
            else if (taken > 0 && cnt[x] == 0) {  // 需要改动的数的数量>0且遇到未出现过的数
                taken--;  // 改动一个数，需要改动的数量-1
                ans += x; // 解释如题前注释，这里是为了计算X+Y 即用到的没有出现过的数相加
            }
        }

        return ans;
    }
};

// map计数
// 用了上面(X + Y) - (P + Q)的方式
// 时间复杂度超出
class Solution {
public:
    int minIncrementForUnique(vector<int>& A) {
        int n = A.size();
        if(n < 2) return 0;
        map<int, int> num;
        int count = 0;
        int ans = 0;
        int tem = 0;
        for(int i = 0; i < n; ++i){
            num[A[i]]++;
        }
        for(auto x : num){
            tem = x.first;
            if (x.second >= 2) {  // 数量大于2个
                int ncount = x.second;  // 这个数重复的次数
                count += x.second - 1;  // 需要改动的数的数量(重复的数量-1)
                ans -= x.first * (x.second - 1);  // 解释如题前注释，这里是为了计算P+Q 即减去(重复出现的数相加之和)
                while(ncount >= 2){
                    if(num.count(tem) != 0){
                        tem++;
                    }else{
                        num[tem]--;  // 未出现过的数标记为-1
                        ncount--;    // 这个数重复的次数-1
                    }
                }
            }
            else if (count > 0 && x.second == -1) {  // 需要改动的数的数量>0且遇到未出现过的数
                count--;  // 改动一个数，需要改动的数量-1
                ans += x.first; // 解释如题前注释，这里是为了计算X+Y 即用到的没有出现过的数相加
            }
        }
        return ans;
    }
};

// 排序
// 先排序，再依次遍历数组元素，若当前元素小于等于它前一个元素，则将其变为前一个数+1。

class Solution {
public:
    int minIncrementForUnique(vector<int>& A) {
        sort(A.begin(),A.end());
        int move = 0;
        // 遍历数组，若当前元素小于等于它的前一个元素，则将其变为前一个数+1
        for (int i = 1; i < A.size(); ++i) {
            if (A[i] <= A[i - 1]) {
                int pre = A[i];
                A[i] = A[i - 1] + 1;
                move += A[i] - pre;
            }
        }
        return move;
    }
};

// 计数排序
// 本地测试通过(6)，Leetcode测试3，2，1，2，1，7通不过(32)

class Solution {
public:
    int minIncrementForUnique(vector<int>& A) {
        // counter数组统计每个数字的个数。
        //（这里为了防止下面遍历counter的时候每次都走到40000，
        // 所以设置了一个maxi，这个数据量不设也行，再额外设置mini也行）
        int counter[40001];
        int maxi = -1;
        for (int i = 0; i < A.size(); ++i) {
            counter[A[i]]++;
            maxi = max(maxi, A[i]);
        }

        // 遍历counter数组，若当前数字的个数cnt大于1个，则只留下1个，其他的cnt-1个后移
        int move = 0;
        for (int num = 0; num <= maxi; ++num) {
            if (counter[num] > 1) {
                int d = counter[num] - 1;
                move += d;
                counter[num + 1] += d;
            }
        }
        // 最后, counter[maxi+1]里可能会有从counter[maxi]后移过来的，counter[maxi+1]里只留下1个，其它的d个后移。
        // 设 maxi+1 = x，那么后面的d个数就是[x+1,x+2,x+3,...,x+d],
        // 因此操作次数是[1,2,3,...,d],用求和公式求和。
        int d = counter[maxi + 1] - 1;
        move += (1 + d) * d / 2;
        return move;
    }
};

// 含路径压缩的线性探测法
// 这道题换句话说，就是需要把原数组映射到一个地址不冲突的区域，映射后的地址不小于原数组对应的元素。
// 比如[3, 2, 1, 2, 1, 7]就映射成了[3, 2, 1, 4, 5, 7]。

// 这道题目其实和解决hash冲突的线性探测法比较相似！
// 如果地址冲突了，会探测它的下一个位置，如果下一个位置还是冲突，继续向后看，直到第一个不冲突的位置为止。

// 关键点：因为直接线性探测可能会由于冲突导致反复探测耗时太长，因此我们可以考虑探测的过程中进行路径压缩。
// 怎么路径压缩呢？就是经过某条路径最终探测到一个空位置x后，将这条路径上的值都变成空位置所在的下标x，
// 那么假如下次探测的点又是这条路径上的点，则可以直接跳转到这次探测到的空位置x，从x开始继续探测。

class Solution {
private:
    // 线性探测寻址（含路径压缩）
    int findPos(vector<int> &pos, int a) {
        int b = pos[a];
        // 如果a对应的位置pos[a]是空位，直接放入即可。
        if (b == -1) {
            pos[a] = a;
            return a;
        }
        // 否则向后寻址
        // 因为pos[a]中标记了上次寻址得到的空位，因此从pos[a]+1开始寻址就行了（不需要从a+1开始）。
        b = findPos(pos, b + 1);
        pos[a] = b; // 寻址后的新空位要重新赋值给pos[a]哦，路径压缩就是体现在这里。
        return b;
    }
public:
    int minIncrementForUnique(vector<int>& A) {
        vector<int> pos(80000, -1);  // -1表示空位
        int move = 0;
        // 遍历每个数字a对其寻地址得到位置b, b比a的增量就是操作数。
        for (int i = 0; i < A.size(); ++i) {
            int b = findPos(pos, A[i]);
            move += b - A[i];
        }
        return move;
    }
};
