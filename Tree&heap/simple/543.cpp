// 二叉树的直径：二叉树中从一个结点到另一个节点最长的路径，叫做二叉树的直径
// 注意：任意两个结点都可以，只要是最大路径就行(不一定非得经过根结点)

// 二叉树上的任一“路径”上一定有一个结点是所有其他结点的祖先结点（因为“路径”是由一个个父子关系连接而成的），
// 换个表述方法，对于任一结点，以此结点为根的diameter就可以表示为左子树高度 + 右子树高度，
// 而二叉树的diameter就是所有结点为根的diameter中最大的那个。

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
private:
    int maxd = 0;
public:
    int diameterOfBinaryTree(TreeNode* root) {
        dfs(root);
        return maxd;
    }
    int dfs(TreeNode* rt){
        if (rt == NULL) return 0; // 访问到空节点了，返回0
        int l = dfs(rt->left); // 左儿子为根的子树的深度
        int r = dfs(rt->right); // 右儿子为根的子树的深度
        maxd = max(maxd, l + r); // 计算路径长度 并更新maxdiameter
        return max(l, r) + 1; // 返回该节点为根的子树的深度
    }
};