static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 暴力解法
// 两点确定一条直线，直线方程可以表示为(y2 - y1)/(x2 - x1) = (y - y2)/(x - x2)

class Solution {
    // test() 方法1，转化为乘积
    bool test(int x1, int y1, int x2, int y2, int x, int y) {
	    return (long long)(y2 - y1) * (x - x2) == (long long)(y - y2) * (x2 - x1);
    }

    // test() 方法2，约分为最简形式，然后分别判断分子和分母是否相等
    // 需要求分子和分母的最大公约是，利用gcd算法
/*    bool test(int x1, int y1, int x2, int y2, int x, int y) {
        int g1 = gcd(y2 - y1, x2 - x1);
        if(y == y2 && x == x2){
            return true;
        }
        int g2 = gcd(y - y2, x - x2);
        return (y2 - y1) / g1 == (y - y2) / g2 && (x2 - x1) / g1 == (x - x2) / g2;
    }

    int gcd(int a, int b) {
        while (b != 0) {
            int temp = a % b;
            a = b;
            b = temp;
        }
        return a;
    }
*/
public:
    int maxPoints(vector<vector<int>>& points) {
        int len = points.size();
        if (len < 3) return len;  // 小于等于两个点直接返回
        int i = 0;
        for (; i < len - 1; ++i) {  // 所有点都在一个点上
            if(points[i][0] != points[i + 1][0] || points[i][1] != points[i + 1][1]) break;
        }
        if (i == len - 1) {
            return len;
        }
        int max = 0;
        for (i = 0; i < len; ++i) {
            for (int j = i + 1; j < len; ++j) {
                if (points[i][0] == points[j][0] && points[i][1] == points[j][1]) {
                    continue;
                }
                int tempMax = 0;
                for (int k = 0; k < len; k++) {
                    if (k != i && k != j) {
                        if (test(points[i][0], points[i][1], points[j][0], points[j][1], points[k][0], points[k][1]))
                            tempMax++;
                    }

                }
                if (tempMax > max) {
                    max = tempMax;
                }
            }
        }
        //加上直线本身的两个点
        return max + 2;
    }
};

// 利用斜率求解
// 选定一个点，任意点与这个点形成直线的斜率相同则在同一条直线上

class Solution {
    int gcd(int a, int b) {
        while (b != 0) {
            int temp = a % b;
            a = b;
            b = temp;
        }
        return a;
    }
public:
    int maxPoints(vector<vector<int>>& points) {
        int len = points.size();
        if (len < 3) {
            return len;
        }
        int res = 0;
        // 遍历每个点
        for (int i = 0; i < len; i++) {
            int duplicate = 0;
            int m = 0;  // 保存经过当前点的直线中，最多的点
            unordered_map<string, int> map;
            for (int j = i + 1; j < len; j++) {
                // 求出分子分母
                int x = points[j][0] - points[i][0];
                int y = points[j][1] - points[i][1];
                if (x == 0 && y == 0) {
                    duplicate++;
                    continue;
                }
                // 进行约分,使用gcd是为了防止精度损失，否则直接用double来存也可以
                int g = gcd(x, y);
                x = x / g;
                y = y / g;
                string key = to_string(x) + "@" + to_string(y);
                map[key]++;
                m = max(m, map[key]);
            }
            // 1 代表当前考虑的点，duplicate 代表和当前的点重复的点
            res = max(res, m + duplicate + 1);
        }
        return res;
    }
};