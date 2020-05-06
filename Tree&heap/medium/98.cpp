static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 中序遍历查看是否升序序列

class Solution {
    vector<int> judge;
    void inorder(TreeNode* root){
        if(root){
            inorder(root->left);
            judge.emplace_back(root->val);
            inorder(root->right);
        }
    }
public:
    bool isValidBST(TreeNode* root) {
        inorder(root);
        int n = judge.size();
        if(n < 2) return true;
        for(int i = 1; i < judge.size(); ++i){
            if(judge[i-1] >= judge[i]) return false;
        }
        return true;
    }
};

// 递归简洁版

class Solution {
public:
    bool helper(TreeNode* root, long long lower, long long upper) {
        if (root == nullptr) return true;
        if (root -> val <= lower || root -> val >= upper) return false;
        return helper(root -> left, lower, root -> val) && helper(root -> right, root -> val, upper);
    }
    bool isValidBST(TreeNode* root) {
        return helper(root, LONG_MIN, LONG_MAX);
    }
};

// 迭代

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        stack<TreeNode*> stack;
        long long inorder = (long long)INT_MIN - 1;

        while (!stack.empty() || root != nullptr) {
            while (root != nullptr) {
                stack.push(root);
                root = root -> left;
            }
            root = stack.top();
            stack.pop();
            // 如果中序遍历得到的节点的值小于等于前一个 inorder，说明不是二叉搜索树
            if (root -> val <= inorder) return false;
            inorder = root -> val;
            root = root -> right;
        }
        return true;
    }
};