static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 双指针
// 总是交换 一串(或者一个)0的第一个 与 这串(个)0后面的第一个非0数

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int len = nums.size();
        if(len < 2) return ;
        int p1 = 0, p2 = 0;
        for(; p2 < len; ++p2){
            if(nums[p1] != 0) p1++;
            else if(nums[p1] == 0 && nums[p2] != 0){
                swap(nums[p1], nums[p2]);
                p1++;
            }
        }
    }
};

// 也可以理解为快排思想
// 这里可以参考快速排序的思想，快速排序首先要确定一个待分割的元素做中间点x，
// 然后把所有小于等于x的元素放到x的左边，大于x的元素放到其右边。
// 这里可以用0当做这个中间点，把不等于0(注意题目没说不能有负数)的放到中间点的左边，等于0的放到其右边。
