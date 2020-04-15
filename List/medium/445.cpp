// 栈
// 若直接将两个链表中储存的数取出来相加再生成新的链表，可能会遇到有符号数大于INT_MAX或者小于INT_MIN
// 这样操作起来会很不方便
// 逆序按位处理则方便些
// 逆序处理，似乎一般都会用到栈

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if(!l1 || !l2)return l1 == nullptr ? l2 : l1;  // 处理传进来有nullptr的情况
        stack<int> stack1;
        stack<int> stack2;
        while (l1 != nullptr) {
            stack1.push(l1->val);
            l1 = l1->next;
        }
        while (l2 != nullptr) {
            stack2.push(l2->val);
            l2 = l2->next;
        }

        int carry = 0;  // 进位位
        ListNode* head = nullptr;
        while (!stack1.empty() || !stack2.empty() || carry > 0) {
            int sum = carry;
            if(!stack1.empty()){
                sum += stack1.top();
                stack1.pop();
            }
            if(!stack2.empty()){
                sum += stack2.top();
                stack2.pop();
            }
            ListNode* node = new ListNode(sum % 10);
            node->next = head;
            head = node;
            carry = sum / 10;  // 处理进位位
        }
        return head;
    }
};