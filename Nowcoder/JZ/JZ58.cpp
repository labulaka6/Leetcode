static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 递归

class Solution {
private:
    bool dfs(TreeNode* root1, TreeNode* root2){
        if(!root1 && !root2) return true;
        if(!root1 || !root2) return false;
        if(root1->val != root2->val) return false;
        return dfs(root1->left, root2->right) && dfs(root1->right, root2->left);
    }
public:
    bool isSymmetric(TreeNode* root) {
        if(!root) return true;
        return dfs(root->left, root->right);
    }
};

// 迭代 - BFS

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
		if(!root || (!root->left && !root->right)) return true;
		// 用队列保存节点
		queue<TreeNode*> Q;
		// 将根节点的左右孩子放到队列中
		Q.push(root->left);
		Q.push(root->right);
		while(!Q.empty()) {
			// 从队列中取出两个节点，再比较这两个节点
			TreeNode* left = Q.front();
            Q.pop();
			TreeNode* right = Q.front();
            Q.pop();
			// 如果两个节点都为空就继续循环，两者有一个为空就返回false
			if(!left && !right) continue;
			if(!left || !right) return false;
			if(left->val != right->val) return false;
			// 将左节点的左孩子， 右节点的右孩子放入队列
			Q.push(left->left);
			Q.push(right->right);
			// 将左节点的右孩子，右节点的左孩子放入队列
			Q.push(left->right);
			Q.push(right->left);
		}
		return true;
    }
};