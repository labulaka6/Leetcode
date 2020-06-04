static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 哈希表
// 利用哈希表来记录节点，避免每次都遍历链表来找节点

class Solution {
public:
    void reorderList(ListNode* head) {
        unordered_map<int, ListNode*> m;
        int num = 0;
        while(head){
            m[num] = head;
            num++;
            head = head->next;
        }
        num--;
        if(num < 2) return;
        int i = 0;
        while(i < num){
            m[i]->next = m[num];
            i++;
            if(i == num) break;  // 链表长度为偶数时会提前相遇
            m[num]->next = m[i];
            num--;
        }
        m[i]->next = nullptr;
    }
};

// 从中间切断链表，反转第二个链表，然后依次拼接两个链表

class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next || !head->next->next) return;
        //找中点，链表分成两个
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* newHead = slow->next;
        slow->next = nullptr;

        //第二个链表倒置
        newHead = reverseList(newHead);

        //链表节点依次连接
        while (newHead) {
            ListNode* temp = newHead->next;
            newHead->next = head->next;
            head->next = newHead;
            head = newHead->next;
            newHead = temp;
        }

    }

private:
    ListNode* reverseList(ListNode* head) {
        if (!head) return nullptr;
        ListNode* tail = head;
        head = head->next;

        tail->next = nullptr;

        while (head) {
            ListNode* temp = head->next;
            head->next = tail;
            tail = head;
            head = temp;
        }

        return tail;
    }
};

// 递归

class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next || !head->next->next ) return;
        int len = 0;
        ListNode* h = head;
        // 求出节点数
        while (h) {
            len++;
            h = h->next;
        }
        reorderListHelper(head, len);
    }

private:
    ListNode* reorderListHelper(ListNode* head, int len) {
        if (len == 1) {
            ListNode* outTail = head->next;
            head->next = nullptr;
            return outTail;
        }
        if (len == 2) {
            ListNode* outTail = head->next->next;
            head->next->next = nullptr;
            return outTail;
        }
        // 得到对应的尾节点，并且将头结点和尾节点之间的链表通过递归处理
        ListNode* tail = reorderListHelper(head->next, len - 2);
        // 中间链表(已经处理好的中间部分，相当于最终链表的尾部)的头结点。(注：递归最先处理的是最终链表的尾部)
        ListNode* subHead = head->next;
        head->next = tail;
        ListNode* outTail = tail->next;  // 上一层 head 对应的 tail
        tail->next = subHead;
        return outTail;
    }
};