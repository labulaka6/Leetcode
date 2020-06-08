static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 生成图然后BFS

const int INF = 1 << 20;

class Solution {
private:
    unordered_map<string, int> wordId;  // word -> id
    vector<string> idWord;  // id -> word
    vector<vector<int>> edges;  // 图的边

    bool transformCheck(const string& str1, const string& str2) {
        int differences = 0;
        for (int i = 0; i < str1.size() && differences < 2; i++) {
            if (str1[i] != str2[i]) {
                ++differences;
            }
        }
        return differences == 1;
    }
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        int id = 0;
        for (const string& word : wordList) {  // 将wordList里的单词创建映射关系
            if (!wordId.count(word)) {
                wordId[word] = id++;
                idWord.push_back(word);
            }
        }
        if (!wordId.count(endWord)) {  // wordList不包含endword，无法转换
            return {};
        }
        if (!wordId.count(beginWord)) {  // wordList不包含beginword，创建映射关系
            wordId[beginWord] = id++;
            idWord.push_back(beginWord);
        }
        // 创建图
        edges.resize(idWord.size());
        for (int i = 0; i < idWord.size(); i++) {
            for (int j = i + 1; j < idWord.size(); j++) {
                if (transformCheck(idWord[i], idWord[j])) {
                    edges[i].push_back(j);
                    edges[j].push_back(i);
                }
            }
        }
        const int dest = wordId[endWord];
        vector<vector<string>> res;  // 储存结果
        queue<vector<int>> q;  // 用于BFS
        // cost[i] 表示 beginWord 对应的点到第 i 个点的代价（即转换次数）。初始情况下其所有元素初始化为无穷大。
        vector<int> cost(id, INF);
        q.push(vector<int>{wordId[beginWord]});  // beginWord入队
        cost[wordId[beginWord]] = 0;
        while (!q.empty()) {
            vector<int> now = q.front();  // 队首单词序列
            q.pop();
            int last = now.back();  // 当前转换到的单词id
            if (last == dest) {  // 到达endWord
                vector<string> tmp;
                for (int index : now) {
                    tmp.push_back(idWord[index]);
                }
                res.push_back(tmp);
            } else {  // 还未到达endWord
                for (int i = 0; i < edges[last].size(); i++) {
                    int to = edges[last][i];  // edges[last]为当前单词可以转换到的单词的集合
                    // beginWord到last的路径+1 <= beginWord到to的路径时才考虑这条路径
                    // 因为题目要求要找到最短的路径，这里是为了保证找到的路径为最短路径(因为是BFS所以可以保证)
                    if (cost[last] + 1 <= cost[to]) {
                        cost[to] = cost[last] + 1;  // 记录beginWord到to的开销
                        vector<int> tmp(now);  // 维持now不变
                        tmp.push_back(to);  // to加入当前路径
                        q.push(tmp);  // 入队
                    }
                }
            }
        }
        return res;
    }
};