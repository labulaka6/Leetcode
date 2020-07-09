static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        queue<TreeNode*> q;
        q.push(root);
        string res;
        while(!q.empty()){
            auto p = q.front();
            q.pop();
            if(p){
                res += to_string(p->val);
                res += ',';
                q.push(p->left);
                q.push(p->right);
            }else res += "null,";
        }
        return res;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int start = 0, end = 0;
        vector<string> res;
        for( ; end < data.length(); ++end){
            if(data[end] == ','){
                res.emplace_back(data.substr(start, end-start));
                start = end + 1;
            }
        }
        if(res[0] == "null") return nullptr;
        TreeNode* root = new TreeNode(stoi(res[0]));
        queue<TreeNode*> q;
        q.push(root);
        for(int i = 1; i < res.size(); ){
            if(res[i] != "null"){
                TreeNode* p = new TreeNode(stoi(res[i]));
                q.front()->left = p;
                q.push(p);
            }
            i++;
            if(res[i] != "null"){
                TreeNode* p = new TreeNode(stoi(res[i]));
                q.front()->right = p;
                q.push(p);
            }
            i++;
            q.pop();
        }
        return root;
    }
};