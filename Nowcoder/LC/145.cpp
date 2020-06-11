static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 递归

class Solution {
    vector<int> ans;
    void post(TreeNode* root){
        if(root){
            post(root->left);
            post(root->right);
            ans.emplace_back(root->val);
        }
    }
public:
    vector<int> postorderTraversal(TreeNode* root) {
        post(root);
        return ans;
    }
};

// 迭代

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode*> s;
        vector<int> ans;
        while(root || !s.empty()){  // 当前节点不为空或者栈不为空
            if(root){  // 向左遍历
                s.push(root);
                root = root->left;
            }else{  // 遍历到左子树为空的节点
                TreeNode* tmp = s.top();  // 回溯
                if(!tmp->right){  // 右子树也为空，是叶子节点
                    s.pop();
                    ans.push_back(tmp->val);
                    continue;
                }
                root = tmp->right;  // 右子树不为空，从这个子树开始再次向左遍历
                tmp->right = nullptr;  // 切断右子树，使这个节点变为叶子节点
                                       // 此时这个节点的根节点为root，已经被记录，不会影响树的遍历
            }
        }
        return ans;
    }
};

// 迭代模板

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> call;
        if(root) call.push(root);
        while(!call.empty()){
            TreeNode *t = call.top();
            call.pop();
            if(t){
                call.push(t);  // 在右节点之前重新插入该节点，以便在最后处理（访问值）
                call.push(nullptr); // nullptr跟随t插入，标识已经访问过，还没有被处理
                if(t->right) call.push(t->right);
                if(t->left) call.push(t->left);
            }else{
                res.push_back(call.top()->val);
                call.pop();
            }
        }
        return res;
    }
};