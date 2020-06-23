static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 栈
// 记当前节点为 T，上一个节点为 S，那么实际上只有两种情况：
// T 是 S 的左子节点；
// T 是根节点到 S 这一条路径上（不包括 S）某一个节点的右子节点。
// 为什么不包括 S？因为题目中规定了如果节点只有一个子节点，那么保证该子节点为左子节点。
// 在 T 出现之前，S 仍然还是一个叶节点，没有左子节点，因此 T 如果是 S 的子节点，一定是优先变成 S 的左子节点。

// 如果 T 是 S 的左子节点，那么 T 的深度恰好比 S 的深度大 1；
// 在其它的情况下，T 是栈中某个节点（不包括 S）的右子节点，那么我们将栈顶的节点不断地出栈，
// 直到 T 的深度恰好比栈顶节点的深度大 1，此时就找到了 T 的父节点。

class Solution {
public:
    TreeNode* recoverFromPreorder(string S) {
        stack<TreeNode*> path;
        int pos = 0;  // 位置
        while (pos < S.length()) {
            int level = 0;  // 深度
            while (S[pos] == '-') {
                ++level;
                ++pos;
            }
            int value = 0;
            while (pos < S.length() && isdigit(S[pos])) {  // 处理数字
                value = value * 10 + (S[pos] - '0');
                ++pos;
            }
            TreeNode* node = new TreeNode(value);
            if (level == path.size()) {  // 深度为栈的深度(栈顶节点的深度+1)，则这个节点为栈顶节点的左子节点
                if (!path.empty()) {
                    path.top()->left = node;
                }
            }else {  // 深度大于栈的深度
                while (level != path.size()) {  // 找到父节点(深度等于栈的深度)
                    path.pop();
                }
                path.top()->right = node;
            }
            path.push(node);
        }
        while (path.size() > 1) {
            path.pop();
        }
        return path.top();
    }
};