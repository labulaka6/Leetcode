static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// BFS - 迭代

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(!root) return res;
        queue<TreeNode*> Q;
        TreeNode* p;
        Q.push(root);
        while(!Q.empty()){
            vector<int> a;
            int width = Q.size();
            for(int i = 0; i < width; ++i){
                p = Q.front();
                a.emplace_back(p->val);
                Q.pop();
                if(p->left) Q.push(p->left);
                if(p->right) Q.push(p->right);
            }
            res.emplace_back(a);
        }
        return res;
    }
};

// DFS - 递归

class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> levelOrder(TreeNode* root){
        addVector(root,0);      // 调用递归函数
        return res;
    }

    void addVector(TreeNode* root, int level){
        if(root == NULL) return ;
        // level表示层数，也对应二维数组的第一层索引，resize()分配给res level+1个vector<int>
        if(res.size() == level) res.resize(level+1);
        res[level].push_back(root->val);
        addVector(root->left,level+1);
        addVector(root->right,level+1);
    }
};