// 遍历
static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    vector<int> distributeCandies(int candies, int num_people) {
        vector<int> people(num_people, 0);
        for(int i = 0; candies > 0; ++i){
            if(candies > i){
                people[i%num_people] += (i+1);
                candies -= (i+1);
            }else{
                people[i%num_people] += candies;
                candies = 0;
            }
        }
        return people;
    }
};

// 遍历精简版，代码更简洁
class Solution {
public:
    vector<int> distributeCandies(int candies, int num_people) {
        vector<int> ans(num_people,0);
        int i = 0;
        while (candies != 0) {
            ans[i % num_people] += min(candies, i + 1);
            candies -= min(candies, i + 1);
            ++i;
        }
        return ans;
    }
};

// 数学法
// 1. 当前candies最多可以按照规则发给k个同学，第k+1个同学得到的是按规则发剩下的糖果，先计算k;
// 2. 得到k之后，每行长度为num_people, 能得到 a = k/num_people行，第a+1行只有k%num_people 个.
// 3. 竖直来看，就是个等差数列，第一行的元素为首项，接下来计算公差和项数就行了.
// 4. 第i列的和，就是第i个同学能够获取的糖果总数; 最后一个同学获得的糖果数是剩余的糖果.
class Solution {
public:
    vector<int> distributeCandies(int candies, int num_people) {
        int n = 1;
        vector<int> ans(num_people,0);
        while(n*(n+1) <= 2*candies)  //一共可以分多少次 ：n-1 利用等差数列求前n项和的公式
            n++;
        for(int i = 0; i < num_people; ++i){
            int t = (n-1)/num_people + ((n-1)%num_people > i); //对学生i，可以分多少次：t，有的学生会多一次
            ans[i] = (i+1 + i+1 + (t-1)*num_people)*t/2;  //分到糖果数目为：列的（首项+尾项）*项数/2
        }
        ans[(n-1) % num_people] += candies -n*(n-1)/2 ;//将最后剩余的糖果分给最后一个人
        return ans;
    }
};

