// 递归

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(root == nullptr) return 0;
        int l = maxDepth(root->left) + 1;
        int r = maxDepth(root->right) + 1;
        return l > r ? l : r;
    }
};

// DFS
// 同理也可用BFS来解，只需要将stack换为queue即可

class Solution {
public:
    int maxDepth(TreeNode* root) {
        stack<pair<TreeNode*, int>> S;  // 结点 + 深度
        int depth = 0;
        if(root != nullptr) S.push(make_pair(root, 1));
        while(!S.empty()){
            pair<TreeNode*, int> tem = S.top();
            S.pop();
            if(tem.first != nullptr){
                depth = max(tem.second, depth);
                S.push(make_pair(tem.first->left, tem.second + 1));
                S.push(make_pair(tem.first->right, tem.second + 1));
            }
        }
        return depth;
    }
};