static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 递归

// 题目给出s和t两树，求解t是不是s的子树，如果是，那么有三种情况：
// 1. t就等于s本身
// 2. t是s的左子树的子树
// 3. t是s的右子树的子树
// 也就是 return isEqual(s,t) || isSubtree(s.left, t) || isSubtree(s.right, t);
// 也就是递归体在于以上三步，因此，根据第一点，需要一个判断两树相等的函数（同样使用递归）

// 问题变成：如何判断两树（l、r）相等？
// 1. 根节点值相等
// 2. l的左子树和r的左子树相等
// 3. l的右子树和r的右子树相等

class Solution {
    bool isEqual(TreeNode* l, TreeNode* r){
        if(l == nullptr && r == nullptr) return true;  // 两树均空自然相等
        if(l == nullptr || r == nullptr) return false;  // 一空一非空，自然不等
        if(l->val == r->val)  // 递归判断
            return isEqual(l->left, r->left) && isEqual(l->right, r->right);
        return false;
    }
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if(s == nullptr && t == nullptr) return true;
        if(s == nullptr || t == nullptr) return false;
        if(isEqual(s,t)) return true;
        // 根节点不同，那么就不同考虑s和t相等的情形了
        return isSubtree(s->left, t) || isSubtree(s->right, t);
    }
};

// 朴实dfs

class Solution {
public:
    bool check(TreeNode *o, TreeNode *t) {
        if (!o && !t) return true;
        if ((o && !t) || (!o && t) || (o->val != t->val)) return false;
        return check(o->left, t->left) && check(o->right, t->right);
    }

    bool dfs(TreeNode *o, TreeNode *t) {
        if (!o) return false;
        return check(o, t) || dfs(o->left, t) || dfs(o->right, t);
    }

    bool isSubtree(TreeNode *s, TreeNode *t) {
        return dfs(s, t);
    }
};