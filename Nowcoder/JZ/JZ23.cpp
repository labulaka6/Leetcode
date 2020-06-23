static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 递归分治
// 后序遍历定义： [ 左子树 | 右子树 | 根节点 ] ，即遍历顺序为 “左、右、根” 。
// 二叉搜索树定义： 左子树中所有节点的值 < 根节点的值；右子树中所有节点的值 > 根节点的值；其左、右子树也分别为二叉搜索树。

class Solution {
    bool recur(vector<int>& postorder, int i, int j) {
        if(i >= j) return true;  // 子树只有一个节点，无需检查
        int p = i;
        while(postorder[p] < postorder[j]) p++;  // 寻找第一个值大于根节点的节点(即寻找所有左子树节点)
        int m = p;
        while(postorder[p] > postorder[j]) p++;  // 检查右子树节点值是否都大于根节点的值
        // p == j证明右子树所有节点值均大于根节点，同时递归分治判断左子树与右子树是都符合条件
        return p == j && recur(postorder, i, m - 1) && recur(postorder, m, j - 1);
    }
public:
    bool verifyPostorder(vector<int>& postorder) {
        return recur(postorder, 0, postorder.size() - 1);
    }
};

// 辅助单调栈

class Solution {
public:
    bool verifyPostorder(vector<int>& postorder) {
        stack<int> s;
        int root = INT_MAX;
        for(int i = postorder.size() - 1; i >= 0; --i) {
            if(postorder[i] > root) return false;  // root为当前子树的根节点值
            while(!s.empty() && s.top() > postorder[i]){
            	root = s.top();
                s.pop();
            }
            s.push(postorder[i]);
        }
        return true;
    }
};