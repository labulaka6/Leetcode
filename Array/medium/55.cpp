// 一般解法
// 注意：是能否达到最后一个位置

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    bool canJump(vector<int>& nums) {
        bool ans = true;  // 默认可以达到最后一个位置
        int n = nums.size();
        for(int i = 0; i < n - 1; ++i){  // 遍历数组
            if(nums[i] == 0){    // 寻找0，如果没有0必然可以到达，有的话则不一定
                ans = false;    // 找到0则默认不可到达
                for(int j = 0, v = i; v >=0; --v, ++j){  // 寻找可以跳过0这个位置的位置
                    if(nums[v] > j){  // 找到
                        ans = true;  // 修改ans为默认值 即可到达
                        break;  // 继续寻找0
                    }
                }
            }
            if(ans == false) break;  // 如果某个0无法跳过，则必定无法到达最后一个位置
        }
        return ans;
    }
};

// 贪心
// 如果某一个作为 起跳点 的格子可以跳跃的距离是 3，那么表示后面 3 个格子都可以作为 起跳点。
// 可以对每一个能作为 起跳点 的格子都尝试跳一次，把 能跳到最远的距离 不断更新。
// 如果可以一直跳到最后，就成功了。

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int k = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (i > k) return false;
            k = max(k, i + nums[i]);
        }
        return true;
    }
};