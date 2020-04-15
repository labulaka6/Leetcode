// DFS - 可以称为回溯算法

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    // 做减法
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        // 特判
        if (n == 0) {
            return res;
        }

        // 执行深度优先遍历，搜索可能的结果
        dfs("", n, n, res);
        return res;
    }

    //  curStr 当前递归得到的结果
    //  left   左括号还有几个可以使用
    //  right  右括号还有几个可以使用
    //  res    结果集
    void dfs(string curStr, int left, int right, vector<string>& res) {
        // 因为每一次尝试，都使用新的字符串变量，所以无需回溯
        // 在递归终止的时候，直接把它添加到结果集即可，注意与「力扣」第 46 题、第 39 题区分
        if (left == 0 && right == 0) {
            res.push_back(curStr);
            return;
        }

        // 剪枝（左括号可以使用的个数严格大于右括号可以使用的个数，才剪枝，注意这个细节）
        // 左边可用 > 右边可用 代表 右边用的比左边多
        if (left > right) {
            return;
        }

        if (left > 0) {
            dfs(curStr + "(", left - 1, right, res);
        }

        if (right > 0) {
            dfs(curStr + ")", left, right - 1, res);
        }
    }
};

// BFS也可以解这道题，但是需要自己定义结点类，然后用队列来实现，不如DFS直接使用系统栈简洁
// 搜索几乎都是用深度优先遍历（回溯算法）

// 动态规划
// 任何一个括号序列都一定是由 ( 开头，并且第一个 ( 一定有一个唯一与之对应的 )。
// 这样一来，每一个括号序列可以用 (a)b 来表示，其中 a 与 b 分别是一个合法的括号序列（可以为空）。
// v[i]代表i对括号所有可能的组合

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<vector<string>> v(n+1);
        v[0].push_back("");
        for(int i = 1; i <= n; ++i){
            for(int j = 0; j < i; ++j){
                for(string &str1 : v[j]){
                    for(string &str2 : v[i-j-1])
                        v[i].push_back("(" + str2 + ")" + str1);
                }
            }
        }
        return v[n];
    }
};