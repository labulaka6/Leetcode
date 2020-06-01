static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 枚举

class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        int len = candies.size();
        int max = *max_element(candies.begin(), candies.end());
        vector<bool> ans(len, false);
        for(int i = 0; i < len; ++i){
            if(candies[i] + extraCandies >= max) ans[i] = true;
        }
        return ans;
    }
};