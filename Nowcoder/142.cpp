static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 快慢指针

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if(!head || !head->next || !head->next->next) return nullptr;
        ListNode* slow = head->next;
        ListNode* fast = head->next->next;
        while(fast && fast->next && slow != fast){
            slow = slow->next;
            fast = fast->next->next;
        }
        if(slow != fast) return nullptr;
        fast = head;
        while(fast != slow){
            fast = fast->next;
            slow = slow->next;
        }
        return fast;
    }
};