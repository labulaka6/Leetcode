static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 哈希表

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if(!head) return nullptr;
        unordered_map<int, int> m;
        ListNode* cur = head;
        while(cur){
            m[cur->val]++;
            cur = cur->next;
        }
        while(head && m[head->val] > 1){
            head = head->next;
        }
        ListNode* pre = head;
        if(!pre) return nullptr;
        cur = head->next;
        while(cur){
            if(m[cur->val] > 1) pre->next = cur->next;
            else pre = pre->next;
            if(!pre) break;
            cur = pre->next;
        }
        return head;
    }
};

// 迭代

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head) return nullptr;
        ListNode* dummy = new ListNode(-1000);
        dummy->next = head;
        ListNode* slow = dummy;  // 指向已除去重复元素部分的末尾
        // 指向未除去重复元素部分的[头部] 第一个元素是重复元素，这个重复元素的最后一个 或者 第一个元素是不重复元素，指向这个元素
        ListNode* fast = dummy->next;
        while (fast) {
            // 如果存在重复元素，找到这个重复元素的最后一个
            while (fast->next && fast->val == fast->next->val) fast = fast->next;
            // 不是重复元素
            if (slow->next == fast) slow = slow->next;
            // 重复元素
            else slow->next = fast->next;
            fast = fast->next;
        }
        return dummy->next;
    }
};

// 递归

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head)  return nullptr;
        if (head->next && head->val == head->next->val) {  // head本身为重复元素
            // 找到重复元素的最后一个
            while (head->next && head->val == head->next->val) {
                head = head->next;
            }
            // 返回最后一个的后一个元素的调用结果
            return deleteDuplicates(head->next);
        }
        // head为不重复元素
        else head->next = deleteDuplicates(head->next);
        return head;
    }
};