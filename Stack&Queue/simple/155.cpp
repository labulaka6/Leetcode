static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 借助辅助栈

class MinStack {
    stack<int> s;  // 数据栈
    stack<int> min;  // 辅助栈
public:
    /** initialize your data structure here. */
    MinStack() {

    }

    void push(int x) {
        s.push(x);
        // 辅助栈入栈条件(第一个元素或者小于辅助栈栈顶元素)
        if(min.empty() || x <= min.top()) min.push(x);
    }

    void pop() {
        // 两个栈栈顶元素相等则共同出栈
        if(s.top() == min.top()) min.pop();
        s.pop();
    }

    int top() {
        return s.top();
    }

    int getMin() {
        return min.top();
    }
};

// 一个栈实现

class MinStack {
    stack<int> s;
    int min = INT_MAX;
public:
    /** initialize your data structure here. */
    MinStack() {

    }

    void push(int x) {
        // 当前值更小
        if(x <= min){
            // 将之前的最小值保存
            s.push(min);
            // 更新最小值
            min = x;
        }
        s.push(x);
    }

    void pop() {
        //如果弹出的值是最小值，那么将下一个元素更新为最小值
        if(s.top() == min) {
            s.pop();
            min = s.top();
            s.pop();
        }else s.pop();
    }

    int top() {
        return s.top();
    }

    int getMin() {
        return min;
    }
};

// 一个栈实现 - 保存差值

class MinStack {
    stack<long> s;  // 因为需要做减法，可能发生溢出，所以用long
    long min;
public:
    /** initialize your data structure here. */
    MinStack() {

    }

    void push(int x) {
		if (s.empty()) {
			min = x;
			s.push(x - min);
		} else {
			s.push(x - min);
			if (x < min){
				min = x; // 更新最小值
			}
		}
    }

    void pop() {
		if (s.empty()) return;
		long pop = s.top();
        s.pop();
		// 弹出的是负值，要更新 min
		if (pop < 0) {
			min = min - pop;
		}
    }

    int top() {
		long top = s.top();
		// 负数的话，出栈的值保存在 min 中
		if (top < 0) {
			return min;
        // 出栈元素加上最小值即可
		} else {
			return top + min;
		}
    }

    int getMin() {
        return min;
    }
};

// 用链表也可实现
// 在节点中多定义一个min来记录当前最小值
// push()采用头插法，pop()就是head = head->next，
// top()就是return head->val，geiMin()就是return head->min

class MinStack {
    struct Node{
        int value;
        int m;
        Node* next;
        Node(int x, int M) : value(x), m(m), next(nullptr) {}
    };
    Node* head;
public:
    /** initialize your data structure here. */
    MinStack() {

    }

    void push(int x) {
        if(!head){
            Node tem = Node(x, x);
            head = &tem;
        }else{
            // 当前值和之前头结点的最小值较小的做为当前的 min
            Node n = Node(x, min(x, head->m));
            n.next = head;
            head = &n;
        }
    }

    void pop() {
        if(head) head = head->next;
    }

    int top() {
        if(head) return head->value;
        return -1;
    }

    int getMin() {
        if(head) return head->m;
        return -1;
    }
};