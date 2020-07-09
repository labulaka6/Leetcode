static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 排序

class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int ans = 0;
        for(int i = 0; i < nums.size() - 1; ++i){
            if(nums[i] == nums[i+1]){
                ans = nums[i];
                break;
            }
        }
        return ans;
    }
};

// 哈希

class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        unordered_set<int> ust;
        int ans = 0;
        for(int i = 0; i < nums.size(); ++i){
            if(ust.find(nums[i]) != ust.end()){
                ans = nums[i];
                break;
            }else{
                ust.insert(nums[i]);
            }
        }
        return ans;
    }
};

// 原地哈希
// 因为题目给出数组中的数范围为 0 ~ nums.size()-1
// 正好在数组下标范围内，所以可以直接将数组下边作为索引
// nums[i] = i

class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        int i = 0;
        while(i < nums.size()) {
            if(nums[i] == i) {
                i++;
                continue;
            }
            if(nums[nums[i]] == nums[i]) return nums[i];
            swap(nums[i], nums[nums[i]]);  // 把nums[i]换到自己的位置上
        }
        return -1;
    }
};