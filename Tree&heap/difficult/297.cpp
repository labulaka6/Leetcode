static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 层次化 - BFS

class Codec {
private:
    vector<string> split(string &data){  // 根据逗号分割字符串并放入容器
        int start = 0;
        vector<string> res;
        while(1){
            auto end = data.find(',', start);
            if(end == string::npos) break;
            res.push_back(data.substr(start, end-start));
            start = end+1;
        }
        return move(res);
    }

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
        auto vals = split(data);
        queue<TreeNode*> q;
        if(vals[0] == "null") return nullptr;
        q.push(new TreeNode(stoi(vals[0])));
        TreeNode *res = q.front();
        for(int i = 1; i < vals.size(); ){
            if(vals[i] != "null"){
                auto p = new TreeNode(stoi(vals[i]));
                q.push(p);
                q.front()->left = p;
            }
            ++i;
            if(vals[i] != "null"){
                auto p = new TreeNode(stoi(vals[i]));
                q.push(p);
                q.front()->right = p;
            }
            ++i;
            q.pop();
        }
        return res;
    }
};

// 递归 - DFS
// 借助字符串流 i/ostringstream

class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream out;
        serialize(root, out);
        return out.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deserialize(in);
    }
private:
    void serialize(TreeNode* root,ostringstream& out){
        if(root){
            out << root->val << ' ';
            serialize(root->left,out);
            serialize(root->right,out);
        }else{
            out<<"# ";
        }
    }

    TreeNode* deserialize(istringstream& in){
        string val;
        in >> val;
        if(val == "#") return nullptr;
        TreeNode* root = new TreeNode(stoi(val));
        root->left = deserialize(in);
        root->right = deserialize(in);
        return root;
    }
};
