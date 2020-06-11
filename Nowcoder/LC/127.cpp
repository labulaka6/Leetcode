static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// BFS
// 图

class Solution {
private:
    unordered_map<string, int> wordId;  // word->id
    vector<string> idWord;  // id->word
    vector<vector<int>> edges;  // 图的边

    bool check(const string& str1, const string& str2){
        int differences = 0;
        for(int i = 0; i < str1.length() && differences < 2; ++i){
            if(str1[i] != str2[i]) differences++;
        }
        return differences == 1;
    }
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        int id = 0;
        for(const string word : wordList){
            if(!wordId.count(word)){
                wordId[word] = id++;  // word -> id
                idWord.emplace_back(word);  // id -> word
            }
        }
        if(!wordId.count(endWord)) return 0;  // wordList不包含endWord，无法转换
        if(!wordId.count(beginWord)){  // 将beginWord加入映射
            wordId[beginWord] = id++;
            idWord.emplace_back(beginWord);
        }
        // 创建图
        edges.resize(idWord.size());
        for (int i = 0; i < idWord.size(); i++) {
            for (int j = i + 1; j < idWord.size(); j++) {
                if (check(idWord[i], idWord[j])) {
                    edges[i].push_back(j);
                    edges[j].push_back(i);
                }
            }
        }
        const int dest = wordId[endWord];
        vector<vector<string>> res;  // 储存结果
        queue<vector<int>> q;  // 用于BFS
        // cost[i] 表示 beginWord 对应的点到第 i 个点的代价（即转换次数）。初始情况下其所有元素初始化为无穷大。
        vector<int> cost(id, INT_MAX);
        q.push(vector<int>{wordId[beginWord]});  // beginWord入队
        cost[wordId[beginWord]] = 0;
        int ans = 0;
        while (!q.empty()) {
            vector<int> now = q.front();  // 队首单词序列
            q.pop();
            int last = now.back();  // 当前转换到的单词id
            if (last == dest) {  // 到达endWord
                ans = cost[wordId[endWord]] + 1;  // 防止输出INT_MAX,保证输出的正确性
                break;
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
        return ans;
    }
};

// BFS

class Solution{
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList){
        //加入所有节点，访问过一次，删除一个。
        unordered_set<string> s;
        for (auto &i : wordList) s.insert(i);

        queue<pair<string, int>> q;
        //加入beginword
        q.push({beginWord, 1});

        string tmp; //每个节点的字符
        int step;    //抵达该节点的step

        while ( !q.empty() ){
            if ( q.front().first == endWord){
                return (q.front().second);
            }
            tmp = q.front().first;
            step = q.front().second;
            q.pop();

            //寻找下一个单词了
            char ch;
            for (int i = 0; i < tmp.length(); i++){
                ch = tmp[i];
                for (char c = 'a'; c <= 'z'; c++){
                    //从'a'-'z'尝试一次
                    if ( ch == c) continue;
                    tmp[i] = c ;
                    //如果找到的到
                    if (  s.find(tmp) != s.end() ){
                        q.push({tmp, step+1});
                        s.erase(tmp) ; //删除该节点
                    }
                tmp[i] = ch; //复原
                }
            }
        }
        return 0;
    }
};