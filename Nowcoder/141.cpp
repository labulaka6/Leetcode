static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 快慢指针

class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(!head || !head->next) return false;
        ListNode* fast = head->next;
        while(fast != head){
            if(!fast || !fast->next) return false;
            head = head->next;
            fast = fast->next->next;
        }
        return true;
    }
};

// 哈希表
// 空间复杂度为 O(n) 不符合题目要求

class Solution {
public:
    bool hasCycle(ListNode *head) {
        unordered_set<ListNode*> nodes;
        while(head){
            if(nodes.find(head) != nodes.end()) return true;
            nodes.insert(head);
            head = head->next;
        }
        return false;
    }
};