static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 哈希表
// 时间复杂度：O(m+n)
// 空间复杂度：O(min(m,n))

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return intersect(nums2, nums1);
        }
        unordered_map <int, int> m;
        for (int num : nums1) {
            ++m[num];
        }
        vector<int> intersection;
        for (int num : nums2) {
            if (m.count(num)) {
                intersection.push_back(num);
                --m[num];
                if (m[num] == 0) {
                    m.erase(num);
                }
            }
        }
        return intersection;
    }
};

// 排序双指针
// 时间复杂度：O(max(nlogn, mlogm, n+m))
// 空间复杂度：O(1)

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        int length1 = nums1.size(), length2 = nums2.size();
        vector<int> intersection;
        int index1 = 0, index2 = 0;
        while (index1 < length1 && index2 < length2) {
            if (nums1[index1] < nums2[index2]) {
                index1++;
            } else if (nums1[index1] > nums2[index2]) {
                index2++;
            } else {
                intersection.push_back(nums1[index1]);
                index1++;
                index2++;
            }
        }
        return intersection;
    }
};

// 进阶问题1：已排序的数组，使用双指针只需 O(n) 的时间复杂度
// 进阶问题2：将较小的数组哈希计数，随后在另一个数组中根据哈希来寻找。时间复杂度：O(max(n, m))，空间复杂度：O(min(n, m))
// 进阶问题3：如果内存十分小，不足以将数组全部载入内存，那么必然也不能使用哈希这类费空间的算法，只能选用空间复杂度最小的算法，即排序双指针。
//           但是需要改造，一般说排序算法都是针对于内部排序，一旦涉及到跟磁盘打交道（外部排序），则需要特殊的考虑。
//           归并排序是天然适合外部排序的算法，可以将分割后的子数组写到单个文件中，归并时将小文件合并为更大的文件。
//           当两个数组均排序完成生成两个大文件后，即可使用双指针遍历两个文件，如此可以使空间复杂度最低。
