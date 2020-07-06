static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 暴力法
// 超出时间限制 428 / 596 个通过测试用例
// 丑数必为小丑数 *2 或 *3 或 *5

class Solution {
public:
    int nthUglyNumber(int n) {
        vector<bool> dp(2, true);
        int count = 1, i = 1;
        while(count < n){
            i++;
            if(i%5 == 0) dp.push_back(dp[i/5]);
            else if(i%3 == 0) dp.push_back(dp[i/3]);
            else if(i%2 == 0) dp.push_back(dp[i/2]);
            else dp.push_back(false);

            if(dp[i]) count++;
        }
        return i;
    }
};

// 优化 - 动态规划

// 丑数必为小丑数 *2 或 *3 或 *5
// 假设当前存在 3 个数组 nums2, nums3, nums5 分别代表丑数序列从 1 开始分别乘以 2, 3, 5 的序列， 即
// nums2 = {1*2, 2*2, 3*2, 4*2, 5*2, 6*2,...}
// nums3 = {1*3, 2*3, 3*3, 4*3, 5*3, 6*3,...}
// nums5 = {1*5, 2*5, 3*5, 4*5, 5*5, 6*5,...}
// 那么， 最终的丑数序列实际上就是这 3 个有序序列对的合并结果， 计算丑数序列也就是相当于 合并 3 个有序序列。

// 合并 3 个有序序列， 最简单的方法就是每一个序列都各自维护一个指针， 然后比较指针指向的元素的值， 将最小的放入最终的合并数组中， 并将相应指针向后移动一个元素。 这也就是：
// class Solution {
// public:
// 	int nthUglyNumber(int n) {
// 		// ....
// 		dp[i] = min(min(dp[p2] * 2, dp[p3] * 3), dp[p5] * 5);
// 		if (dp[i] == dp[p2] * 2)
// 			p2++;
// 		if (dp[i] == dp[p3] * 3)
// 			p3++;
// 		if (dp[i] == dp[p5] * 5)
// 			p5++;
//                   // ......
// };
// 这段代码所做的事情。

// 合并过程中重复解的处理
// nums2, nums3, nums5 中是存在重复的解的， 例如 nums2[2] == 3*2, nums3[1] == 2*3 都计算出了 6 这个结果，
// 所以在合并 3 个有序数组的过程中， 还需要跳过相同的结果， 这也就是为什么在比较的时候，
// 需要使用 3 个并列的 if... if... if... 而不是 if... else if... else 这种结构的原因。
// 当比较到元素 6 时， if (dp[i] == dp[p2] * 2)...if (dp[i] == dp[p3] * 3)... 可以同时指向 nums2, nums3 中 元素 6 的下一个元素。


class Solution {
public:
    int nthUglyNumber(int n) {
        int a = 0, b = 0, c = 0;
        vector<int> dp(n);
        dp[0] = 1;
        for(int i = 1; i < n; i++) {
            int n2 = dp[a] * 2, n3 = dp[b] * 3, n5 = dp[c] * 5;
            dp[i] = min(min(n2, n3), n5);
            if(dp[i] == n2) a++;
            if(dp[i] == n3) b++;
            if(dp[i] == n5) c++;
        }
        return dp[n - 1];
    }
};