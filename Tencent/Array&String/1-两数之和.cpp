static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 暴力解法

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ans(2);
        for(int i = 0; i < nums.size()-1; ++i){
            for(int j = i+1; j < nums.size(); ++j){
                if(nums[i] + nums[j] == target){
                    ans[0] = i;
                    ans[1] = j;
                    break;
                }
            }
        }
        return ans;
    }
};

// 两遍哈希表

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> m;
        vector<int> ans(2);
        for(int i = 0; i < nums.size(); ++i){
            m[nums[i]] = i;
        }
        for(int i = 0; i < nums.size(); ++i){
            int tem = target - nums[i];
            if(m.find(tem) != m.end() && m[tem] != i){
                ans[0] = i;
                ans[1] = m[tem];
                break;
            }
        }
        return ans;
    }
};

// 一遍哈希表

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> m;
        vector<int> ans(2);
        for(int i = 0; i < nums.size(); ++i){
            int tem = target - nums[i];
            if(m.find(tem) != m.end()){
                ans[0] = m[tem];
                ans[1] = i;
                break;
            }
            m[nums[i]] = i;
        }
        return ans;
    }
};