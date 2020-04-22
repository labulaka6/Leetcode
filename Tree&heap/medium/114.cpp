static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 莫里斯算法
// 将左子树插入到右子树的地方
// 将原来的右子树接到左子树的最右边节点
// 考虑新的右子树的根节点，一直重复上边的过程，直到新的右子树为 null

class Solution {
public:
    void flatten(TreeNode* root) {
        while(root){
            //左子树为 null，直接考虑下一个节点
            if(!root->left){
                root = root->right;
            }else{
                // 找左子树最右边的节点
                TreeNode* pre = root->left;
                while(pre->right){
                    pre = pre->right;
                }
                //将原来的右子树接到左子树的最右边节点
                pre->right = root->right;
                // 将左子树插入到右子树的地方
                root->right = root->left;
                root->left = nullptr;
                // 考虑下一个节点
                root = root->right;
            }
        }
    }
};

// 后序遍历
// 采用先序遍历会导致右孩子结点丢失，故采用后序遍历

class Solution {
    TreeNode* last = nullptr;
public:
    void flatten(TreeNode* root) {
        if (root == nullptr) return;
        flatten(root->left);
        flatten(root->right);
        if (root->left != nullptr) {
            auto pre = root->left;
            while(pre->right != nullptr) pre = pre->right;
            pre->right = root->right;
            root->right = root->left;
            root->left = nullptr;
        }
        root = root->right;
        return;
    }
};