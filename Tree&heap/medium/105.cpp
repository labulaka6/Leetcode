static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 递归拆分

class Solution {
    TreeNode* buildTreeHelper(vector<int>& preorder, int p_start, int p_end, vector<int>& inorder, int i_start, int i_end) {
        // preorder 为空，直接返回 null
        if (p_start == p_end) {
            return nullptr;
        }
        int root_val = preorder[p_start];
        TreeNode* root = new TreeNode(root_val);
        //在中序遍历中找到根节点的位置
        int i_root_index = 0;
        for (int i = i_start; i < i_end; ++i) {
            if (root_val == inorder[i]) {
                i_root_index = i;
                break;
            }
        }
        int leftNum = i_root_index - i_start;
        //递归的构造左子树
        root->left = buildTreeHelper(preorder, p_start + 1, p_start + leftNum + 1, inorder, i_start, i_root_index);
        //递归的构造右子树
        root->right = buildTreeHelper(preorder, p_start + leftNum + 1, p_end, inorder, i_root_index + 1, i_end);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return buildTreeHelper(preorder, 0, preorder.size(), inorder, 0, inorder.size());
    }
};

// 利用哈希表改进

class Solution {
    TreeNode* buildTreeHelper(vector<int>& preorder, int p_start, int p_end, vector<int>& inorder, int i_start, int i_end,
                                    unordered_map<int, int>& map) {
        if (p_start == p_end) {
            return nullptr;
        }
        int root_val = preorder[p_start];
        TreeNode* root = new TreeNode(root_val);
        int i_root_index = map[root_val];
        int leftNum = i_root_index - i_start;
        root->left = buildTreeHelper(preorder, p_start + 1, p_start + leftNum + 1, inorder, i_start, i_root_index, map);
        root->right = buildTreeHelper(preorder, p_start + leftNum + 1, p_end, inorder, i_root_index + 1, i_end, map);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> map;
        for (int i = 0; i < inorder.size(); ++i) {
            map[inorder[i]] = i;
        }
        return buildTreeHelper(preorder, 0, preorder.size(), inorder, 0, inorder.size(), map);
    }
};