static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 暴力解法 - 链表模拟
// 全真模拟
// 超出时间限制  26 / 36 个通过测试用例

class Solution {
public:
    int lastRemaining(int n, int m) {
        list<int> nums;
        for (int i = 0; i < n; i++) {
            nums.push_back(i);
        }
        auto it = nums.begin();
        int ret = *it;
        while (!nums.empty()) {
            for (int i = 0; i < m - 1; i++) {
                it++;
                if (it == nums.end()) it = nums.begin();  // 循环
            }
            ret = *it;
            it = nums.erase(it);  // list erase 操作返回后序的迭代器
            if (it == nums.end()) it = nums.begin();  // 循环
        }
        return ret;
    }
};

// 数学解法 - 约瑟夫环

class Solution {
    int f(int n, int m) {
        if (n == 1)
            return 0;
        int x = f(n - 1, m);
        return (m + x) % n;
    }
public:
    int lastRemaining(int n, int m) {
        return f(n, m);
    }
};

// 迭代版约瑟夫环

class Solution {
public:
    int lastRemaining(int n, int m) {
        int ans = 0;
        // 最后一轮剩下2个人，所以从2开始反推
        for (int i = 2; i <= n; i++) {
            ans = (ans + m) % i;
        }
        return ans;
    }
};