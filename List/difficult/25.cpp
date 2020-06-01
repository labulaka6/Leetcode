static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
};

// 递归

class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* pre = head;
        int count = 0;
        while(pre && count < k){
            pre = pre->next;
            count++;
        }
        // 退出循环后pre指向第k+1个节点
        if(count == k) {
            pre = reverseKGroup(pre, k);
            while(count > 0){
                // head指向本次循环反转指向的节点，temp指向下次循环反转指向的节点
                ListNode* temp = head->next;
                head->next = pre;
                pre = head;
                head = temp;
                count--;
            }
            head = pre;
        }
        return head;
    }
};

// 迭代

class Solution {
    // 反转链表
    ListNode* reverse(ListNode* head) {
        ListNode* pre = nullptr;
        ListNode* curr = head;
        while (curr) {
            ListNode* next = curr->next;
            curr->next = pre;
            pre = curr;
            curr = next;
        }
        return pre;
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0);
        dummy.next = head;

        ListNode* pre = &dummy;  // 本次反转起始位置的前一个节点
        ListNode* end = &dummy;  // 本次反转的最后一个节点

        while (end->next) {
            for (int i = 0; i < k && end; ++i) end = end->next;  // 本次反转的最后一个节点
            if (!end) break;  // 为空则说明不足k个，无需反转
            ListNode* start = pre->next;  // 本次反转的起始位置
            ListNode* next = end->next;  // 下一次反转的起始位置
            end->next = nullptr;
            pre->next = reverse(start);  // 进行反转
            start->next = next;  // 反转后的链表与剩余链表对接
            pre = start;  // 重置pre
            end = pre;   // 充值end
        }
        return dummy.next;
    }
};