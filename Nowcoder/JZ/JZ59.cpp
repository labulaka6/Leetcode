static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 栈

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(!root) return res;
        stack<TreeNode*> odd;
        stack<TreeNode*> even;
        odd.push(root);
        while(!odd.empty()){
            vector<int> oddline;
            while(!odd.empty()){
                TreeNode* tmp = odd.top();
                oddline.emplace_back(tmp->val);
                odd.pop();
                if(tmp->left) even.push(tmp->left);
                if(tmp->right) even.push(tmp->right);
            }
            res.emplace_back(oddline);

            vector<int> evenline;
            while(!even.empty()){
                TreeNode* tmp = even.top();
                evenline.emplace_back(tmp->val);
                even.pop();
                if(tmp->right) odd.push(tmp->right);
                if(tmp->left) odd.push(tmp->left);
            }
            if(evenline.size() > 0) res.emplace_back(evenline);
        }
        return res;
    }
};

// 层次遍历 + 倒序

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> queue;
        vector<vector<int>> res;
        if(root) queue.push(root);
        while(!queue.empty()) {
            vector<int> tmp;
            for(int i = queue.size(); i > 0; i--) {
                TreeNode* node = queue.front();
                queue.pop();
                tmp.emplace_back(node->val);
                if(node->left) queue.push(node->left);
                if(node->right) queue.push(node->right);
            }
            if(res.size() % 2 == 1) reverse(tmp.begin(), tmp.end());
            res.emplace_back(tmp);
        }
        return res;
    }
};

// 双端队列

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if(!root) return res;
        bool flag = true;  // 从左向右打印为true，从右向左打印为false
        deque<TreeNode*> q;
        q.push_back(root);
        while (!q.empty()){
            int n = q.size();
            vector<int> out;
            TreeNode* node;
            while (n > 0){
                if(flag){  // 奇数行前取后放：从左向右打印，所以从前边取，后边放入
                    node = q.front();
                    q.pop_front();
                    if (node->left) q.push_back(node->left);  // 下一层顺序存放至尾
                    if (node->right) q.push_back(node->right);
                }else{  // 偶数行后取前放： 从右向左，从后边取，前边放入
                    node = q.back();
                    q.pop_back();
                    if (node->right) q.push_front(node->right);  // 下一层逆序存放至首
                    if (node->left) q.push_front(node->left);
                }
                out.push_back(node->val);
                n--;
            }
            flag = !flag;
            res.push_back(out);
        }
        return res;
    }
};