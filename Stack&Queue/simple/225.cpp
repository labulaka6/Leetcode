// 单队列实现
// 入栈时先入队 然后将队列中除最后入队的元素重新一次出队入队
// 出栈时直接出队

class MyStack {
    queue<int> que;
public:
    /** Initialize your data structure here. */
    MyStack() {

    }

    /** Push element x onto stack. */
    void push(int x) {
        que.push(x);
        for(int i = 0; i < que.size() - 1; ++i){
            que.push(que.front());
            que.pop();
        }
    }

    /** Removes the element on top of the stack and returns that element. */
    int pop() {
        int n = que.front();
        que.pop();
        return n;
    }

    /** Get the top element. */
    int top() {
        return que.front();
    }

    /** Returns whether the stack is empty. */
    bool empty() {
        return que.empty();
    }
};

