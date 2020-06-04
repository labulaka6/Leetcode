static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// map

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        map<int,int> n;
        int ans = 0;
        for(int i = 0; i < nums.size(); ++i){
            n[nums[i]] == 1? n[nums[i]] = 2: n[nums[i]] = 1;
        }
        for(int j = 0; j < nums.size(); ++ j){
            if(n[nums[j]] == 1)  ans = nums[j];
        }
        return ans;
    }
};


// 哈希
// 第一次出现，插入哈希集
// 第二次出现，冲哈希集内删除
// 最后剩下的就是那个只出现一次的数字

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        unordered_set<int> S;
        int ans;
        for(auto i : nums){
            if(S.count(i)) S.erase(i);
            else S.insert(i);
        }
        for(auto j : S)  ans = j;
        return ans;
    }
};

// 排序然后双指针

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for(int i = 0, j = 1; j < nums.size(); i += 2, j += 2){
            if(nums[i] != nums[j])  return nums[i];
        }
        return nums[nums.size() - 1];
    }
};

// 异或 - 位运算
// 任何一个数字异或它自己都等于0。
// 也就是说，如果从头到尾依次异或数组中的每一个数字，那么最终的结果刚好是那个只出现一次的数字，
// 因为那些出现两次的数字全部在异或中抵消掉了，0异或某个数字就等于某个数字。
// XOR 满足交换律和结合律

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans = nums[0];
        for(int i = 1; i < nums.size(); ++ i){
            ans = ans ^ nums[i];
        }
        return ans;
    }
};