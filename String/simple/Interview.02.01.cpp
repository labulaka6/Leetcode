static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 哈希表

class Solution {
public:
    ListNode* removeDuplicateNodes(ListNode* head) {
        if(!head) return head;
        unordered_set<int> uset = {head->val};
        ListNode* cur = head;
        while(cur->next){
            if(!uset.count(cur->next->val)){
                uset.insert(cur->next->val);
                cur = cur->next;
            }
            else cur->next = cur->next->next;
        }
        return head;
    }
};