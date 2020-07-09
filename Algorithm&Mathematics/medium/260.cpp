static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 哈希

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        vector<int> res;
        unordered_map<int, int> m;
        for(int num : nums){
            m[num]++;
        }
        unordered_map<int, int>::iterator it;
        for(it = m.begin(); it != m.end(); ++it){
            if(it->second == 1) res.emplace_back(it->first);
            if(res.size() == 2) break;
        }
        return res;
    }
};

// 位运算
// 对于是用补码的环境，a和-a相与可以获得a最低的非0位。-a就是a取反加1
// 比如a的二进制是 ??????10000，取反就是??????01111，加1就是??????10000。
// 前面?的部分是和原来a相反的，相与必然都是0，所以最后整体相与的结果就是00000010000。

class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int m = 0;
        for(int num : nums){  // 异或的结果为两个出现一次的数的异或的结果
            m ^= num;
        }
        int n = m & (-m);  // 取异或结果的最后一位
        vector<int> res(2, 0);
        for(int num : nums){  // 根据异或结果的最后一位将数组分为两组，可以保证每组只存在一个只出现一次的数
            if((num & n) == 0) res[0] ^= num;
            else res[1] ^= num;
        }
        return res;
    }
};