// 单指针法
// 第一遍遍历链表计数
// 第二遍遍历一半然后返回

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        int n = 0;
        ListNode* p = head;
        while(p != nullptr){
            n++;
            p = p -> next;
        }
        for(int i = 0; i < n/2; ++i){
            head = head -> next;
        }
        return head;
    }
};

// 快慢指针法
// 可以优化上面方法，用两个指针 slow 与 fast 一起遍历链表。slow 一次走一步，fast 一次走两步。
// 那么当 fast 到达链表的末尾时，slow 必然位于中间。

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
};