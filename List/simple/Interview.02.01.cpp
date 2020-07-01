static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// set去重 - 一次遍历

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

// 递归

class Solution {
    ListNode* removeDuplicateNodesHelper(ListNode* head, unordered_set<int>& uset) {
        if (!head) return head;
        if (uset.count(head->val)) return removeDuplicateNodesHelper(head->next, uset);
        uset.insert(head->val);
        head->next = removeDuplicateNodesHelper(head->next, uset);
        return head;
    }
public:
    ListNode* removeDuplicateNodes(ListNode* head) {
        unordered_set<int> uset;
        return removeDuplicateNodesHelper(head, uset);
    }
};

// 位运算
// 固定模m，则任意一个整数x，都可以表示为 x = k*m + b。代码中m=32，即任意一个值val都由k和b唯一确定。
// 代码中 bits[cur->val / 32] |= 1 << (cur->val % 32)就是记录当前cur->val，
// 数组bits[k]的二进制表达的第b位为1，则表示值为k*32+b的数已经出现过
// if里面就是判断，cur->next的值是否出现过。
// 若出现则&结果不为0，跳过cur的下一个节点
// 若没出现&结果为0，链表接上

class Solution {
public:
    ListNode* removeDuplicateNodes(ListNode* head) {
        vector<int> bits(20000/32 + 1, 0);
        ListNode* cur = head;
        while (cur && cur->next) {
            bits[cur->val / 32] |= 1 << (cur->val % 32);
            if ((bits[cur->next->val / 32] & (1 << (cur->next->val % 32))) != 0)
                cur->next = cur->next->next;
            else
                cur = cur->next;
        }
        return head;
    }
};