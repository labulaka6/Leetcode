// 暴力法 - 数组：
static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class MaxQueue {
    int q[20000];   // 总操作数小于10000，20000绰绰有余
    int begin = 0, end = 0;   // 开始，结束位置
public:
    MaxQueue() {
    }

    int max_value() {
        int ans = -1;
        for (int i = begin; i != end; ++i)  // 遍历取出最大的
            ans = max(ans, q[i]);
        return ans;
    }

    void push_back(int value) {
        q[end++] = value;
    }

    int pop_front() {
        if (begin == end)
            return -1;
        return q[begin++];
    }
};

// 两个队列 - 维护一个单调的双端队列：
// queue就是正常的队列，负责push和pop
// deque用来存放最大值
// 如果新的value大于deque尾端的值，那么deque一直进行pop_back操作，直到尾端的值大于等于value 或者为空
// 再将value压入deque的尾部
// 每次取max_value，返回deque首部的值
// 当que进行pop操作时，如果que首部的值等于deque首部的值，那么deque同样需要进行pop_front操作

// 之所以deque可以这样做
// 是因为那些比当前push_back元素小的元素值都会在当前元素之前被pop出去，所以不会存在这些元素成为最大值的情况。
// (PS：做这种题把握好队列先入先出的特性还是蛮重要的。)
class MaxQueue {
    queue<int> que;
    deque<int> dq;
public:
    MaxQueue() {

    }

    int max_value() {
        return que.empty()?-1:dq.front();
    }

    void push_back(int value) {
        que.push(value);
        while(!dq.empty()&&dq.back()<value)
            dq.pop_back();
        dq.push_back(value);
    }

    int pop_front() {
        if(que.empty())
            return -1;
        int t=que.front();
        que.pop();
        if(t==dq.front())
            dq.pop_front();
        return t;
    }
};