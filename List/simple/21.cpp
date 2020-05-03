static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode head(0);
        ListNode* p = &head;
        while(l1 && l2){
            if(l1->val <= l2->val){
                p->next = l1;
                l1 = l1->next;
                p = p->next;
            }else{
                p->next = l2;
                l2 = l2->next;
                p = p->next;
            }
        }
        if(l1 || l2) p->next = l1 == nullptr ? l2 : l1;
        return head.next;
    }
};