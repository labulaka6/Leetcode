// 递归

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
    vector<int> ans;
    void mid(TreeNode* root){
        if(root){
            mid(root->left);
            ans.push_back(root->val);
            mid(root->right);
        }

    }
public:
    vector<int> inorderTraversal(TreeNode* root) {
        mid(root);
        return ans;
    }
};

// 迭代 - 颜色标记法
// 使用颜色标记节点的状态，新节点为白色，已访问的节点为灰色。
// 如果遇到的节点为白色，则将其标记为灰色，然后将其右子节点、自身、左子节点依次入栈。
// 如果遇到的节点为灰色，则将节点的值输出。

class Solution {
	vector<int>ans;
public:
	vector<int> inorderTraversal(TreeNode* root) {
		int white = 0;
		int gray = 1;
		stack<pair<int, TreeNode*>>s;
		s.push(make_pair(white,root));
		while (!s.empty())
		{
			int color = s.top().first;
			TreeNode* t = s.top().second;
			s.pop();
			if (t == NULL) continue;
			if (color == white)
			{
				s.push(make_pair(white, t->right));
				s.push(make_pair(gray, t));
				s.push(make_pair(white, t->left));
			}
			else ans.push_back(t->val);
		}
		return ans;
	}
};

// 一般的遍历方法

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> S;
        TreeNode* curr = root;
        while (curr != nullptr || !S.empty()) {
            while (curr != nullptr) {
                S.push(curr);
                curr = curr->left;
            }
            curr = S.top();
            S.pop();
            res.push_back(curr->val);
            curr = curr->right;
        }
        return res;
    }
};

// 莫里斯遍历 - 不破坏原结构

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> nodes;
        while (root) {
            if (root -> left) {
                TreeNode* pre = root -> left;
                while (pre -> right && pre -> right != root) {  // 寻找左子树的最右结点
                    pre = pre -> right;
                }
                if (!pre -> right) {  // 左子树最右结点还未连接到root
                    pre -> right = root;
                    root = root -> left;
                } else {  // 左子树已遍历过，防止无限循环
                    pre -> right = NULL;
                    nodes.push_back(root -> val);
                    root = root -> right;
                }
            } else {
                nodes.push_back(root -> val);
                root = root -> right;
            }
        }
        return nodes;
    }
};

// 莫里斯遍历 - 破坏原结构
// 效率更高

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        TreeNode* curr = root;
        TreeNode* pre;
        while (curr != nullptr) {
            if (curr->left == nullptr) {  // 无左子树
                res.push_back(curr->val);
                curr = curr->right;
            } else { // 存在左子树
                pre = curr->left;
                while (pre->right != nullptr) { // 找到左子树最右结点
                    pre = pre->right;
                }
                pre->right = curr; // 将原根结点作为 左子树最右结点 的右结点
                TreeNode* temp = curr;
                curr = curr->left; // 根节点调整
                temp->left = nullptr; // 原根结点左子树置空，防止无限循环
            }
        }
        return res;
    }
};