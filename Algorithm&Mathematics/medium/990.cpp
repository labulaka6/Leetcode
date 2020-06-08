static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 并查集

class UnionFind {
private:
    vector<int> parent;

public:
    UnionFind() {
        parent.resize(26);
        iota(parent.begin(), parent.end(), 0);  // 初始化将父节点指向自己
    }

    int find(int index) {
        if (index == parent[index]) {
            return index;
        }
        parent[index] = find(parent[index]);  // 完全路径压缩
        return parent[index];
    }
    // int find(int index) {
    //     while(index != parent[index]){
    //         parent[index] = parent[parent[index]];  // 隔代路径压缩
    //         index = parent[index];
    //     }
    //     return index;
    // }

    void unite(int index1, int index2) {
        parent[find(index1)] = find(index2);
    }
};

class Solution {
public:
    bool equationsPossible(vector<string>& equations) {
        UnionFind uf;
        for (const string& str: equations) {
            if (str[1] == '=') {
                int index1 = str[0] - 'a';
                int index2 = str[3] - 'a';
                uf.unite(index1, index2);
            }
        }
        for (const string& str: equations) {
            if (str[1] == '!') {
                int index1 = str[0] - 'a';
                int index2 = str[3] - 'a';
                if (uf.find(index1) == uf.find(index2)) {
                    return false;
                }
            }
        }
        return true;
    }
};