// 数学解法 - 求最大公约数
// 此问题可简化为 ax+by=z
// 贝祖定理：若x,y是整数,且gcd(x,y)=d，那么对于任意的整数a,b,ax+by都一定是d的倍数，
//          特别地，一定存在整数a,b，使ax+by=d成立。
// 即判断z是否为x,y最大公约数的倍数的问题
// 特别解释一下，若a为负，则相当于y往x中倒水，
// 每填满一次将x倒空一次(填满了才倒，最后一次填水时y可能不为空)，b为负亦然
static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
    int gcd(int x, int y){
        return y == 0 ? x : gcd(y, x%y);
    }
public:
    bool canMeasureWater(int x, int y, int z) {
        if(z == 0) return true;
        if(x + y < z) return false;
        if(x < y) swap(x, y);
        if(y == 0) return x == z;
        int n = gcd(x, y);
        return z%n == 0;
    }
};

// BFS
// 将状态图画出来，利用图的BFS求解

class Solution {
    pair<int, int> op(int type, const pair<int, int> &state, int x, int y) {
        switch(type) {
            case 0 : return make_pair(x, state.second);  // 倒满x
            case 1 : return make_pair(state.first, y);   // 倒满y
            case 2 : return make_pair(0, state.second);  // 倒空x
            case 3 : return make_pair(state.first, 0);   // 倒空y
            case 4 :{
                int move = min(state.first, y-state.second);  // x倒入y直到x为空或者y为满
                return make_pair(state.first - move, state.second + move);
            }
            case 5 : {
                int move = min(x-state.first, state.second);  // y倒入x直到y为空或者x为满
                return make_pair(state.first + move, state.second - move);
            }
        }
        return make_pair(0,0);  // type输入不在范围内
    }
    struct HashPair {  // 自定hash函数避免key冲突
        size_t operator()(const pair<int, int> &key) const noexcept
	    {
		    return size_t(key.first)*100000007 + key.second;
	    }
    };
public:
    bool canMeasureWater(int x, int y, int z) {
        unordered_set<pair<int,int>, HashPair> mark;  // 用unordered_set来储存状态
        queue<pair<int,int>> q;   // 用队列来实现bfs
        q.push(make_pair(0,0));   // 初始状态入队
        while(q.empty() == false) {   // 遍历队列
            auto f = q.front();
            q.pop();
            if(f.first + f.second == z) {   // 满足条件
                return true;
            }
            for(int i = 0; i < 6; i++) {   // 当前状态的各种下一状态入队
                auto next = op(i, f, x, y);  // 下一状态
                if(mark.find(next) != mark.end()) {  // 当前状态已经出现过，跳出本次循环，为了提高效率
                    continue;
                }
                mark.insert(next); // 记录本次状态
                q.push(next);  // 入队
            }
        }
        return false;
    }
};

// 本题同样可用DFS求解
// 将队列改为栈即可，不再赘述