static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    vector<int> levelOrder(TreeNode* root) {
        queue<TreeNode*> q;
        vector<int> res;
        if(!root) return res;
        q.push(root);
        while(!q.empty()){
            auto p = q.front();
            q.pop();
            res.emplace_back(p->val);
            if(p->left) q.push(p->left);
            if(p->right) q.push(p->right);
        }
        return res;
    }
};