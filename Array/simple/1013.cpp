// 方法：寻找切分点

// 将数组 A 中的所有数的和记为 sum(A)。根据题目可以得知，每一个非空部分的和都应当是 sum(A) / 3。
// 因此需要找到索引 i 和 j 使得：
// A[0] + A[1] + ... + A[i] = sum(A) / 3;
// A[i + 1] + A[i + 2] + ... + A[j] = sum(A) / 3。
// 这等价于 A[0] + A[1] + ... + A[j] = sum(A) / 3 * 2 且 j > i。

// 首先需要找出索引 i。具体地，从第一个元素开始遍历数组 A 并对数组中的数进行累加。
// 当累加的和等于 sum(A) / 3 时，就将当前的位置置为索引 i。
// 由于数组中的数有正有负，可能会得到若干个索引 i0, i1, i2, ...，从 A[0] 到这些索引的数之和均为 sum(A) / 3。
// 那么应该选取那个索引呢？直觉告诉我们，应该贪心地选择最小的那个索引 i0，这也是可以证明的：
// ---------------------------------------------------------------------------------------------------
// 假设最终的答案中我们选取了某个不为 i0 的索引 ik 以及另一个索引 j，那么根据上面的两条要求，有：
// A[0] + A[1] + ... + A[ik] = sum(A) / 3;
// A[0] + A[1] + ... + A[j] = sum(A) / 3 * 2 且 j > ik。
// 然而 i0 也是满足第一条要求的一个索引，因为 A[0] + A[1] + ... + A[i0] = sum(A) / 3 并且 j > ik > i0，
// 我们可以将 ik 替换为 i0，因此选择最小的那个索引是合理的。
// ---------------------------------------------------------------------------------------------------
// 这一段说明其实可以理解为：从第一个开始累加到i0 = sum(A)/3,且从第一个开始累加到ik = sum(A)/3
// 即从i0累加到ik = 0

// 在选择了 i0 作为 i 之后，从 i0 + 1 开始继续遍历数组 A 并进行累加，当累加的和等于 sum(A) / 3 * 2 时，
// 就得到了索引 j，可以返回 true 作为答案。如果我们无法找到索引 i 或索引 j，
// 或者 sum(A) 本身无法被 3 整数，那么我们返回 false。


//下面这段函数的主要作用就是提高输入输出的速度，具体解释放在了印象笔记
static const auto _ = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    bool canThreePartsEqualSum(vector<int>& A) {
        int s = accumulate(A.begin(), A.end(), 0);  //sum(A)
        if (s % 3 != 0) {
            return false;
        }
        int target = s / 3;
        int n = A.size(), i = 0, cur = 0;
        while (i < n) {
            cur += A[i];
            if (cur == target) {
                break;
            }
            ++i;
        }
        if (cur != target) {   //没找到sum(A)/3
            return false;
        }
        int j = i + 1;
        while (j + 1 < n) {  // 需要满足最后一个数组非空,相当于 j < n -1
            cur += A[j];
            if (cur == target * 2) {
                return true;
            }
            ++j;
        }
        return false;
    }
};

// 另一种代码，同一种思想，但代码更简洁
// class Solution {
// public:
//     bool canThreePartsEqualSum(vector<int>& A) {
//         int sum = accumulate(A.begin(), A.end(), 0);
//         if (sum % 3 != 0) {
//             return false;
//         }
//         int count = 0, subSum = 0;
//         for (int i = 0; i < A.size() - 1; i ++) {
//             subSum += A[i];
//             if (subSum == sum / 3) {
//                 count ++;
//                 subSum = 0;
//             }
//             if (count == 2) {
//                 return true;
//             }
//         }
//         return false;
//     }
// };