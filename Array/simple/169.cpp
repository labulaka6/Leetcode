// 投票算法
// 如果我们把众数记为 +1+1，把其他数记为 -1−1，将它们全部加起来，显然和大于 0，
// 从结果本身我们可以看出众数比其他数多。
// 相当于自己人投票赞成票，别人投反对票(这里相当于自己人只投自己人，其他人均投反对票)

static const auto _ = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int candidate = -1;
        int count = 0;
        for (int num : nums) {
            if (num == candidate)
                ++count;
            else if (--count < 0) {
                candidate = num;
                count = 1;
            }
        }
        return candidate;
    }
};

// 哈希表解法：
// 使用哈希映射（HashMap）来存储每个元素以及出现的次数。
// 对于哈希映射中的每个键值对，键表示一个元素，值表示该元素出现的次数。
// 用一个循环遍历数组 nums 并将数组中的每个元素加入哈希映射中。
// 在这之后，遍历哈希映射中的所有键值对，返回值最大的键。
// 同样也可以在遍历数组 nums 时候使用打擂台的方法，维护最大的值，这样省去了最后对哈希映射的遍历。

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> counts;
        int majority = 0, cnt = 0;
        for (int num: nums) {
            ++counts[num];
            if (counts[num] > cnt) {
                majority = num;
                cnt = counts[num];
            }
        }
        return majority;
    }
};

// 排序
// 题目中保证会有一个众数(即占数组宽度一半以上的数)
// 所以排序后 n/2 处必为这个众数

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        return nums[nums.size() / 2];
    }
};

// 随机化(具有随机性，不建议选择)
// 因为超过 n/2 的数组下标被众数占据了，这样随机挑选一个下标对应的元素并验证，有很大的概率能找到众数。

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        while (true) {
            int candidate = nums[rand() % nums.size()];
            int count = 0;
            for (int num : nums)
                if (num == candidate)
                    ++count;
            if (count > nums.size() / 2)
                return candidate;
        }
        return -1;
    }
};

// 分治法(个人认为此算法与哈希法差不多，但哈希法更简单)
// 如果数 a 是数组 nums 的众数，如果我们将 nums 分成两部分，那么 a 必定是至少一部分的众数。
// 可以使用反证法来证明这个结论。假设 a 既不是左半部分的众数，也不是右半部分的众数，
// 那么 a 出现的次数少于 l / 2 + r / 2 次，
// 其中 l 和 r 分别是左半部分和右半部分的长度。由于 l / 2 + r / 2 <= (l + r) / 2，
// 说明 a 也不是数组 nums 的众数，因此出现了矛盾。所以这个结论是正确的。
// 这样一来，就可以使用分治法解决这个问题：
// 将数组分成左右两部分，分别求出左半部分的众数 a1 以及右半部分的众数 a2，随后在 a1 和 a2 中选出正确的众数。

// 使用经典的分治算法递归求解，直到所有的子问题都是长度为 1 的数组。
// 长度为 1 的子数组中唯一的数显然是众数，直接返回即可。
// 如果回溯后某区间的长度大于 1，必须将左右子区间的值合并。
// 如果它们的众数相同，那么显然这一段区间的众数是它们相同的值。
// 否则，需要比较两个众数在整个区间内出现的次数来决定该区间的众数。

class Solution {
    int count_in_range(vector<int>& nums, int target, int lo, int hi) {  //[lo, hi]区间中target出现的次数
        int count = 0;
        for (int i = lo; i <= hi; ++i)
            if (nums[i] == target)
                ++count;
        return count;
    }
    int majority_element_rec(vector<int>& nums, int lo, int hi) {  //找出[lo, hi]区间的众数
        if (lo == hi)
            return nums[lo];
        int mid = (lo + hi) / 2;
        int left_majority = majority_element_rec(nums, lo, mid);
        int right_majority = majority_element_rec(nums, mid + 1, hi);
        if (count_in_range(nums, left_majority, lo, hi) > (hi - lo + 1) / 2)
            return left_majority;
        if (count_in_range(nums, right_majority, lo, hi) > (hi - lo + 1) / 2)
            return right_majority;
        return -1;
    }
public:
    int majorityElement(vector<int>& nums) {
        return majority_element_rec(nums, 0, nums.size() - 1);
    }
};