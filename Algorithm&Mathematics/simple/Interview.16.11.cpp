static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 数学

class Solution {
public:
    vector<int> divingBoard(int shorter, int longer, int k) {
        if(k == 0) return vector<int> ();
        if(shorter == longer) return vector<int> (1, shorter*k);
        vector<int> res(k+1);
        for(int i = 0; i <= k; ++i){
            res[i] = i * longer + (k - i) * shorter;
        }
        return res;
    }
};