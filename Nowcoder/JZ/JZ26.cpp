static const auto _ = []{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// DFS
// 二叉搜索树的中序遍历为递增序列

class Solution {
    Node* head, pre;
    void dfs(Node* cur){
        if(cur){
            dfs(cur->left);
            if(pre) pre->right = cur;
            else head = cur;
            cur->left = pre;
            pre = cur;
            dfs(cur->right);
        }
    }
public:
    Node* treeToDoublyList(Node* root) {
        if(!root) return root;
        dfs(root);
        head->left = pre;
        pre->right = head;
        return head;
    }
};