static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 抽屉原理：桌上有十个苹果，要把这十个苹果放到九个抽屉里，无论怎样放，我们会发现至少会有一个抽屉里面放不少于两个苹果。

// 思路：如果题目不限制：

// 不能更改原数组（假设数组是只读的）；
// 只能使用额外的 O(1) 的空间。

// 容易想到的方法有：
// 1.使用哈希表(unordered_set)判重，这违反了限制 2；
// 2.将原始数组排序(sort())，排序以后，重复的数相邻，即找到了重复数，这违反了限制 1；
// 3.使用类似「力扣」第 41 题：“缺失的第一个正数” 的思路，当两个数发现要放在同一个地方的时候，就发现了这个重复的元素，这违反了限制 1；
// 4.既然要定位数，这个数恰好是一个整数，可以在“整数的有效范围内”做二分查找，但是比较恶心的一点是得反复看整个数组好几次，本文就介绍通过二分法定位数；
// 5.还可以使用“快慢指针”来完成，不过这种做法太有技巧性了，不是通用的做法，官方的题解就提供了这种做法。

// 二分法1

class Solution {
public:
    int findDuplicate(vector<int> &nums) {
        int len = nums.size();
        int left = 1;
        int right = len - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            int cnt = 0;
            for (int num:nums) {
                if (num <= mid) {
                    cnt++;
                }
            }

            // 根据抽屉原理，小于等于 4 的数的个数如果严格大于 4 个，
            // 此时重复元素一定出现在 [1, 4] 区间里，这里注意，不是数组中的区间，而是数值大小的区间

            if (cnt > mid) {
                // 重复的元素一定出现在 [left, mid] 区间里
                right = mid;
            } else {
                // if 分析正确了以后，else 搜索的区间就是 if 的反面
                // [mid + 1, right]
                // 注意：此时需要调整中位数的取法为上取整
                left = mid + 1;
            }
        }
        return left;
    }
};

// 二分法2，本质上与二分法1相同

class Solution {
public:
    int findDuplicate(vector<int> &nums) {
        int len = nums.size();
        int left = 1;
        int right = len - 1;

        while (left < right) {
            int mid = left + (right - left + 1) / 2;

            int cnt = 0;
            for (int num:nums) {
                if (num < mid) {
                    cnt++;
                }
            }

            // 根据抽屉原理，严格小于 4 的数的个数如果大于等于 4 个，
            // 此时重复元素一定出现在 [1, 3] 区间里

            if (cnt >= mid) {
                // 重复的元素一定出现在 [left, mid - 1] 区间里
                right = mid - 1;
            } else {
                // if 分析正确了以后，else 搜索的区间就是 if 的反面
                // [mid, right]
                // 注意：此时需要调整中位数的取法为上取整
                left = mid;
            }
        }
        return left;
    }
};

// 快慢指针1
// 假设有这样一个样例：[1,2,3,4,5,6,7,8,9,5]。
// 如果按照上面的循环下去我们就会得到这样一个路径: 1 2 3 4 5 [6 7 8 9] [6 7 8 9] [6 7 8 9] . . .
// 这样就有了一个环，也就是6 7 8 9。point会一直在环中循环的前进。
// 这时我们设置两个一快(fast)一慢(slow)两个指针，一个每次走两步，一个每次走一步，
// 这样让他们一直走下去，直到他们在重复的序列中相遇，(必然是有环才能相遇)
// slow和fast会在环中相遇，先假设一些量：起点到环的入口长度为m，环的周长为c，
// 在fast和slow相遇时slow走了n步。则fast走了2n步，fast比slow多走了n步，而这n步全用在了在环里循环（n%c==0）。
// (因为slow走了n步已经在环里面了，所以fast的第二个n步必然全在环中)
// 当fast和last相遇之后，我们设置第三个指针finder，它从起点开始和slow(在fast和slow相遇处)同步前进，
// 当finder和slow相遇时，就是在环的入口处相遇，也就是重复的那个数字相遇。

// 为什么finder和slow相遇在入口？
// fast和slow相遇时，slow在环中行进的距离是n-m，其中n%c==0。
// 这时我们再让slow前进m步——也就是在环中走了n步了。
// 而n%c==0即slow在环里面走的距离是环的周长的整数倍，就回到了环的入口了，而入口就是重复的数字。
// 我们不知道起点到入口的长度m，所以弄个finder和slow一起走，他们必定会在入口处相遇。


class Solution {
public:
    int findDuplicate(vector<int> &nums) {
        // 找到两个指针的交点
        int slow = nums[0];
        int fast = nums[0];
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while (slow != fast);

        // 找到“循环”的入口
        int finder = nums[0];
        while (finder != slow) {
            finder = nums[finder];
            slow = nums[slow];
        }

        return finder;
    }
};

// 快慢指针2

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int fast = 0, slow = 0;
        while(true){
            fast = nums[nums[fast]];
            slow = nums[slow];
            if(fast == slow)
                break;
        }
        int finder = 0;
        while(true){
            finder = nums[finder];
            slow = nums[slow];
            if(slow == finder)
                break;
        }
        return finder;
    }
};