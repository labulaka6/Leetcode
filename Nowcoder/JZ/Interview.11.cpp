static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int minArray(vector<int>& numbers) {
        int ans = numbers[0];
        for(int i = 1; i < numbers.size(); ++i){
            if(ans > numbers[i]){
                ans = numbers[i];
                break;
            }
        }
        return ans;
    }
};