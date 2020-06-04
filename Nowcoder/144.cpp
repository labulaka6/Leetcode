static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 递归

class Solution {
    vector<int> ans;
    void pre(TreeNode* root){
        if(root){
            ans.emplace_back(root->val);
            pre(root->left);
            pre(root->right);
        }
    }
public:
    vector<int> preorderTraversal(TreeNode* root) {
        pre(root);
        return ans;
    }
};

// 迭代

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> s;
        vector<int> ans;
        while (root || !s.empty()) {
            while (root) {
                ans.emplace_back(root->val);
                s.push(root);
                root = root->left;
            }
            root = s.top()->right;
            s.pop();
        }
        return ans;
    }
};

// 迭代模板

class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;  // 保存结果
        stack<TreeNode*> call;  // 调用栈
        if(root) call.push(root);  // 首先介入root节点
        while(!call.empty()){
            TreeNode *t = call.top();
            call.pop();  // 访问过的节点弹出
            if(t){
                if(t->right) call.push(t->right);  // 右节点先压栈，最后处理
                if(t->left) call.push(t->left);
                call.push(t);  // 当前节点重新压栈（留着以后处理），因为先序遍历所以最后压栈
                call.push(nullptr);  // 在当前节点之前加入一个空节点表示已经访问过了
            }else{  // 空节点表示之前已经访问过了，现在需要处理除了递归之外的内容
                res.push_back(call.top()->val);  //call.top()是nullptr之前压栈的一个节点，也就是上面call.push(t)中的那个t
                call.pop();  // 处理完了，第二次弹出节点（彻底从栈中移除）
            }
        }
        return res;
    }
};