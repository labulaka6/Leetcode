static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 暴力法 - 超出时间限制

class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int n = nums.size();
        int count = 0;  // 优美子数组个数
        for(int i = 0; i < n - k + 1; ++i){
            int tem = 0;  // 奇数个数
            bool is = false;  // 是否已有三个奇数
            for(int j = i; j < n; ++j){  // 寻找以i开头的优美子数组个数
                if(nums[j]%2 != 0){
                    if(is) break;
                    tem++;
                    if(tem == k){
                        count++;
                        is = true;
                    }
                }else{
                    if(is) count++;
                }
            }
            if(!is) break;
        }
        return count;
    }
};

// 数学
// odd[i]为数组中第i个奇数的下标
// 假如找到了k个连续的奇数(中间可能夹着偶数，不影响)
// 然后k个奇数前面有连续的l个偶数，后面有连续的r个偶数
// 则这k个奇数可以形成(l+1)*(k+1)个优美子数组
// 即(odd[i] - odd[i - 1]) * (odd[i + k] - odd[i + k - 1])

class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int n = (int)nums.size();
        int odd[n + 2], ans = 0, cnt = 0;
        for (int i = 0; i < n; ++i) {
            if (nums[i] & 1) odd[++cnt] = i;
        }
        odd[0] = -1, odd[++cnt] = n;  // 为了处理边界问题
        for (int i = 1; i + k <= cnt; ++i) {
            ans += (odd[i] - odd[i - 1]) * (odd[i + k] - odd[i + k - 1]);
        }
        return ans;
    }
};

// 滑动窗口
// 大体与上面数学思路一致

// 使用一个 vector<int> odd 记录奇数的索引，并在头尾插入两条假数据

// 使用滑动窗口，
// 1. i 为窗口开始， j 为窗口结束
// 2. 保证窗口内有 k + 1 个奇数，即 odd.size() - i > k
// 3. 当滑到一个窗口的时候，计算刚脱离窗口的前面的个数 left = odd[i] - odd[i - 1]
// 4. 计算在窗口内的后面两个奇数之间的个数 right = j - odd[odd.size() - 2]
// 5. 从 i 到 odd[odd.size() - 2] 含有 k 个奇数的「优美子数组」组合数为 left * right
// 6. 结果累加

// 结束遍历后，返回结果

class Solution {
public:
    int numberOfSubarrays(vector<int>& nums, int k)
    {
        vector<int> odd;
        odd.push_back(-1);

        int ans = 0;
        int i = 1;
        for (int j = 0; j <= nums.size(); j++)
        {
            if (j == nums.size() || (nums[j] & 1))
            {
                odd.push_back(j);
            }

            if (odd.size() - i > k)
            {
                int left = odd[i] - odd[i - 1];
                int right = j - odd[odd.size() - 2];
                ans += left * right;
                i++;
            }
        }
        return ans;
    }
};

// 前缀和 + 差分
// odd为目前奇数个数
// cnt[odd]为第odd个奇数出现的位置与上一个奇数出现位置之间偶数的个数 + 1;
// 每次计算以数组中每一位为最后一位的优美子数组的个数

class Solution {
    vector<int> cnt;
public:
    int numberOfSubarrays(vector<int>& nums, int k) {
        int n = (int)nums.size();
        cnt.resize(n + 1, 0);
        int odd = 0, ans = 0;
        cnt[0] = 1;
        for (int i = 0; i < n; ++i) {
            odd += nums[i] & 1;  // 当前奇数个数
            ans += odd >= k ? cnt[odd - k] : 0;
            cnt[odd] += 1;
        }
        return ans;
    }
};