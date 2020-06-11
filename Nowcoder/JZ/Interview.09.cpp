static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 基础解法

class CQueue {
public:
    stack<int> st1;
    stack<int> st2;

    CQueue() {}

    void appendTail(int value) {
        st1.push(value);
    }

    int deleteHead() {
        if (st1.empty()) return -1;

        while (!st1.empty()){ // 1 -> 2
            int tmp = st1.top();
            st1.pop();
            st2.push(tmp);
        }
        // delete head
        int res = st2.top();
        st2.pop();
        while (!st2.empty()){ // 1 <- 2
            int temp = st2.top();
            st2.pop();
            st1.push(temp);
        }
        return res;
    }
};

// 优化

class CQueue {
public:
    stack<int> st1;
    stack<int> st2;

    CQueue() {}

    void appendTail(int value) {
        st1.push(value);
    }

    int deleteHead() {
        if (!st2.empty()){  // st2不为空，已经有反转过的元素
            int res = st2.top();
            st2.pop();
            return res;
        }
        if(st1.empty()) return -1;  // 否则st1为空(即st1，st2均为空)

        while (!st1.empty()){ // 否则(即st1不为空，st2为空)，1 -> 2
            int tmp = st1.top();
            st1.pop();
            st2.push(tmp);
        }

        int res = st2.top();
        st2.pop();
        return res;
    }
};