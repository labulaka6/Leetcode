static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 哈希 + 排序

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> res;
        unordered_map<int, int> hash;
        for (auto a : nums){
            hash[a]++;
        }
        // 因为sort只能对有序容器排序，所以将map转成vector
        vector<pair<int, int>> hashv(hash.begin(), hash.end());
        sort(hashv.begin(), hashv.end(), [](pair<int, int>& a, pair<int, int>& b){return a.second > b.second; });
        auto a = hashv.begin();
        while (k--){
            res.emplace_back(a->first);
            a++;
        }
        return res;
    }
};

// 哈希 + 小根堆

class Solution {
public:
    struct cmp{
        bool operator()(pair<int, int>& a, pair<int, int>& b){ return a.second > b.second; }
    };

    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> res;
        unordered_map<int, int> hash;
        for (auto a : nums){
            hash[a]++;
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> freq;
        for (auto a : hash){
            freq.push(a);
            if (freq.size() > k) freq.pop();
        }
        while (!freq.empty()){
            res.push_back(freq.top().first);
            freq.pop();
        }
        return res;
    }
};