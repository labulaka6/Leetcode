static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 递归

class Solution {
    vector<TreeLinkNode*> res;
    void traverse(TreeLinkNode* root){
        if(root){
            traverse(root->left);
            res.emplace_back(root);
            traverse(root->right);
        }
    }
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode){
        TreeLinkNode* root = pNode;
        while(root->next){  // 寻找根节点
            root = root->next;
        }
        traverse(root);
        for(int i = 0; i < res.size(); ++i){
            if(res[i] == pNode && i < res.size()-1) return res[i+1];
        }
        return nullptr;
    }
};

// 分析
// 以该二叉树为例，中序遍历为：{D,B,H,E,I,A,F,C,G}
//         A
//       /   \
//     B       C
//    / \     / \
//   D   E   F   G
//      / \
//     H   I
// 仔细观察，可以把中序下一结点归为几种类型：
// 1. 有右子树，下一结点是右子树中的最左结点，例如 B，下一结点是 H
// 2. 无右子树，且结点是该结点父结点的左子树，则下一结点是该结点的父结点，例如 H，下一结点是 E
// 3. 无右子树，且结点是该结点父结点的右子树，则我们一直沿着父结点追朔，
//    直到找到某个结点是其父结点的左子树，如果存在这样的结点，那么这个结点的父结点就是我们要找的下一结点。
//    例如 I，下一结点是 A；例如 G，并没有符合情况的结点，所以 G 没有下一结点

class Solution {
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode){
        // 1
        if (pNode->right) {
            TreeLinkNode* pRight = pNode->right;
            while (pRight->left) {
                pRight = pRight->left;
            }
            return pRight;
        }
        // 2
        if (pNode->next && pNode->next->left == pNode) {
            return pNode->next;
        }
        // 3
        if (pNode->next) {
            TreeLinkNode* pNext = pNode->next;
            while (pNext->next && pNext->next->right == pNext) {
                pNext = pNext->next;
            }
            return pNext->next;
        }
        return nullptr;
    }
};