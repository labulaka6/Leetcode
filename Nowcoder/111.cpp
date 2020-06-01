static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// BFS - 迭代
// 将队列改为栈即为DFS，但是需要在循环中每次遇到叶子节点时更新最小深度

class Solution {
public:
    int minDepth(TreeNode* root) {
        queue<pair<TreeNode*, int>> Q;
        if(root) Q.push(pair<TreeNode*, int> {root, 1});
        int min = 0;
        while(!Q.empty()){
            pair<TreeNode*, int> tem = Q.front();
            Q.pop();
            root = tem.first;
            min = tem.second;
            if(!root->left && !root->right) break;
            if(root->left) Q.push(pair<TreeNode*, int> {root->left, min+1});
            if(root->right) Q.push(pair<TreeNode*, int> {root->right, min+1});
        }
        return min;
    }
};

// DFS - 递归1

class Solution {
public:
    int minDepth(TreeNode* root) {
        // 此题需注意叶子节点的定义，比较抽象，可以想象一下输入为[1,null,2]的情况，
        // 此时如果单纯返回 1 + min(minDepth(root->left), minDepth(root->right))，则得 1，因为结点1的左子节点深度计算出来为 0，
        // 而实际上，节点2才是符合要求的节点。所以不能单纯的递归比较2个子节点谁的深度小。

        // 首先，节点为空，直接返回0
        if(root == nullptr) return 0;

        // 其次，若当前节点的左右子节点均存在，说明***当前节点不是叶子节点，其孩子节点的性质也无法判定***，故返回较小的孩子节点深度
        if(root->left && root->right) return 1 + min(minDepth(root->left), minDepth(root->right));

        // 最后，若当前节点的左右子节点有一个不存在，则说明***当前节点的子节点中存在叶子节点***，故返回不为空的孩子节点（叶子节点）的深度
        // 当然了，若当前节点的左右子节点都不存在，那它就是叶子节点，总深度直接 +1 就好了，也符合这个 return 句法。
        return 1 + max(minDepth(root->left), minDepth(root->right));
    }
};

// DFS - 递归2

class Solution {
public:
    int minDepth(TreeNode* root) {
        if(!root) return 0;
        int m1 = minDepth(root->left);
        int m2 = minDepth(root->right);
        //1.如果左孩子和右孩子有为空的情况，直接返回m1+m2+1
        //2.如果都不为空，返回较小深度+1
        return !root->left || !root->right ? m1 + m2 + 1 : min(m1, m2) + 1;
    }
};