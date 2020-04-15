// 递归遍历

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if(t1 == nullptr) return t2;
        if(t2 == nullptr) return t1;
        t1->val += t2->val;
        t1->left = mergeTrees(t1->left, t2->left);
        t1->right = mergeTrees(t1->right, t2->right);
        return t1;
    }
};

// 迭代

class Solution {
public:
	TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
		if (t1 == NULL) return t2;
		if (t2 == NULL) return t1;
		stack<TreeNode*>s;
		s.push(t1);
		s.push(t2);
		while (!s.empty()){
			TreeNode* s2 = s.top();
			s.pop();
			TreeNode* s1 = s.top();
			s.pop();
			s1->val = s1->val + s2->val;
			if (s1->left == NULL) s1->left = s2->left;
			else if (s1->left != NULL && s2->left != NULL){
				s.push(s1->left);
				s.push(s2->left);
			}
			if (s1->right == NULL) s1->right = s2->right;
			else if (s1->right != NULL && s2->right != NULL){
				s.push(s1->right);
				s.push(s2->right);
			}
		}
		return t1;
	}
};