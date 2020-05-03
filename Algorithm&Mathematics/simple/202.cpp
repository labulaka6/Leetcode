static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 用hashset检测循环

class Solution {
    int auxiliary(int n){
        int res = 0;
        int tem;
        while(n > 0){
            tem = n%10;
            res += tem*tem;
            n /= 10;
        }
        return res;
    }
public:
    bool isHappy(int n) {
        unordered_set<int> seen;
        while(n != 1 && seen.find(n) == seen.end()){
            seen.insert(n);
            n = auxiliary(n);
        }
        return n == 1;
    }
};

// 快慢指针法

class Solution {
    int auxiliary(int n){
        int res = 0;
        int tem;
        while(n > 0){
            tem = n%10;
            res += tem*tem;
            n /= 10;
        }
        return res;
    }
public:
    bool isHappy(int n) {
        int slowRunner = n;
        int fastRunner = auxiliary(n);
        while (fastRunner != 1 && slowRunner != fastRunner) {
            slowRunner = auxiliary(slowRunner);
            fastRunner = auxiliary(auxiliary(fastRunner));
        }
        return fastRunner == 1;
    }
};



// 数学
// 只有一个循环：44→16→37→58→89→145→42→20→4。所有其他数字都在进入这个循环的链上，或者在进入 1 的链上

class Solution {
    unordered_set<int> cycleMembers = {4, 16, 37, 58, 89, 145, 42, 20};
    int auxiliary(int n){
        int res = 0;
        int tem;
        while(n > 0){
            tem = n%10;
            res += tem*tem;
            n /= 10;
        }
        return res;
    }
public:
    bool isHappy(int n) {
        while (n != 1 && cycleMembers.find(n) == cycleMembers.end()) {
            n = auxiliary(n);
        }
        return n == 1;
    }
};
