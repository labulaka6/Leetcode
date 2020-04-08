// 求最大公约数
// 只有当X为所有数字数目的最大公约数的约数时，才存在可能的分组

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
    int cnt[10000];
public:
    bool hasGroupsSizeX(vector<int>& deck) {
        for (auto x: deck) cnt[x]++;  // 计数，记录数字数目
        int g = -1;
        for (int i = 0; i < 10000; ++i){
            if(cnt[i]) {  // 数目不为1
                if (~g) g = gcd(g, cnt[i]);  // ~g是0 if(~g)就等于if(g!=-1)
                else g = cnt[i];
            }
        }
        return g >= 2;
    }
};

// 素数筛
// 其实只需要枚举从2到最小数字数目之间的素数即可
// 不是素数的话肯定有更小的整数可以整除这个素数

class Solution {
    bool initFlag = false;
    vector<int> primes;  // 存放素数
public:
    bool hasGroupsSizeX(vector<int>& deck) {
        if(initFlag == false) {
            initFlag = true;
            // 标记数组，如果mark[i] == false 且 i>=2，则认为 i 是素数。初始时假设都是素数
            bool mark[10000] = {0};
            for(int i = 2; i < 10000; i++) {
                if(mark[i]) {  // 不是素数直接跳过
                    continue;
                }
                primes.push_back(i);  // 是素数放入容器
                for(int j = i + i; j < 10000; j += i) {  // 素数的倍数一定是非素数
                    mark[j] = true;
                }
            }
        }

        unordered_map<int, int> cnt;
        for(auto v : deck) {
            cnt[v]++;  // 计数，记录数字数目
        }
        auto minIter = cnt.begin();
        for(auto it = cnt.begin(); it != cnt.end(); it++) {
            if(it->second < minIter->second) {
                minIter = it;  // 在数字数目中选出最小值
            }
        }
        if(minIter->second <= 1) {  // 最小值为1，不存在素数，不可能存在分组
            return false;
        }
        for(auto v : primes) {
            if(deck.size() % v) {  // 先检查v能否被deck.size()整除
                continue;
            }
            if(v > minIter->second) {  // 这个素数已经比最小值大
                break;
            }
            bool flag = true;
            for(auto it = cnt.cbegin(); flag && it != cnt.cend(); ++it) {  // 遍历数字的数目
                if(it->second % v) {  // 相当于if(it->second % v ！= 0)
                    flag = false;
                }
            }
            if(flag) {
                return true;
            }
        }
        return false;
    }
};
