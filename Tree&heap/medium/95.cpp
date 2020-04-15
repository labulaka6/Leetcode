// 动态规划

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    // 生成二叉搜索树集合
    void cat(int k, vector<TreeNode*> &F, vector<TreeNode*> F1, vector<TreeNode*> F2){

        for(int i = 0; i < F1.size(); ++i){
            for(int j = 0;j < F2.size(); ++j){
                TreeNode* root=new TreeNode(k);
                root->left = F1[i];
                // 由于F2[j]所有二叉树由1,...,j的节点形成，当F2[j]被当做右子树时，其节点值应该是1+k+1,...,j+k+1.
                root->right = treeAdd(F2[j],k);
                F.push_back(root);
            }
        }
    }
    // 将右子树的结点值转换为 1+k+1,...,j+k+1
    TreeNode* treeAdd(TreeNode* T,int k){
        TreeNode* head=NULL;
        if(T!=NULL){
            //当二叉树节点值变化时，不能像左子树那样共享空间，需要重新开辟空间存储节点值变化的二叉树。
            head = new TreeNode(T->val + k);
            head->left = treeAdd(T->left, k);
            head->right = treeAdd(T->right,k);
        }
        return head;
    }
public:
    vector<TreeNode*> generateTrees(int n) {
        vector<vector<TreeNode*>> F;  // 动态规划数组，F[n] 记录n个节点可以构成的所有二叉树。
        if(n == 0)
            return {};  // 返回[]
        F.push_back({{}});  // F[0]需要记录[[]]。上一行的返回值太奇葩。

        vector<TreeNode*> ans;
        // 这里使用了动态内存分配，在生产环境中使用时要记得使用delete释放内存
        TreeNode *head = new TreeNode(1);
        ans.push_back(head);  // F[1],1个节点只有一种二叉树
        F.push_back(ans);
        if(n == 1)
            return F[1];

        for(int i = 2; i <= n; ++i){
            vector<TreeNode*> ans;  // 记录F[i], i个节点可以构成的二叉树。
            for(int k = 1;  k<= i; ++k){  // 分为i种情况，依次记录
                // 以k为根节点时，其左子树是F[k-1]的任意一颗二叉树，其右子树是F[i-k]的任意一颗二叉树。
                cat(k, ans, F[k-1], F[i-k]);
            }
            F.push_back(ans);
        }
        return F[n];
    }
};