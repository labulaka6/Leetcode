static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// DFS

class Solution {
private:
    Node* dfs(Node* node, unordered_map<Node*, Node*>& lookup) {
        if (!node) return nullptr;
        if (lookup.count(node)) return lookup[node];
        Node* clone = new Node(node->val);
        lookup[node] = clone;
        for (Node* n : node->neighbors) clone->neighbors.push_back(dfs(n, lookup));
        return clone;
    }
public:
    Node* cloneGraph(Node* node) {
        unordered_map<Node*, Node*> lookup;
        return dfs(node, lookup);
    }
};

// BFS

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;
        unordered_map<Node*, Node*> lookup;
        Node* clone = new Node(node->val);
        lookup[node] = clone;
        queue<Node*> queue;
        queue.push(node);
        while (!queue.empty()) {
            Node* tmp = queue.front();
            queue.pop();
            for (Node* n : tmp->neighbors) {
                if (!lookup.count(n)) {
                    lookup[n] = new Node(n->val);
                    queue.push(n);
                }
                lookup[tmp]->neighbors.push_back(lookup[n]);
            }
        }
        return clone;
    }
};