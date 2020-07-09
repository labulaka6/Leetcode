static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 遍历

class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        int mid = target/2 + 1;  // 连续整数相加的和等于target,这个数列中最大的数不会超过target/2 + 1
        int count = 0;  // 记录连续数列的和
        vector<vector<int>> ans;  // 答案
        for(int i = 1; i <= mid; i++){  // 从1开始到mid
            vector<int> l;  // 连续数列
            for(int j = i; count < target; j++){  // 从i开始累加
                count += j;
                l.push_back(j);
            }
            if(count == target){  // 满足条件
                ans.push_back(l);
            }
            count = 0;
        }
        return ans;
    }
};

// 数学
// 如果有两个连续的数之和等于target,那么相差为1,(target - 1) % 2 == 0,
// 且数组一定是从 (target - 1) / 2开始的,数组的元素就是2个；
// 如果是3个连续的数组，那么三个数之间相差为1、2，(target - 1 - 2) % 3 == 0，
// 且数组一定是从 (target - 1 - 2) / 3开始的，数组元素是3个，
// 依次类推，但是注意target必须是大于0的数，且res需要倒序。

class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>> res;  // 答案
        int i = 1;
        while(target > 0){
            target -= i++;  // i+1个连续整数的数组
            if(target > 0 && target % i == 0){  // 依次遍历是否有i+1个连续整数的数组满足条件
                vector<int> tmp;
                for(int j = 0; j < i; j++) tmp.push_back(target / i + j);  // 满足的数组为tem
                res.push_back(tmp);  // 放入res
            }
        }
        reverse(res.begin(), res.end());
        return res;
    }
};