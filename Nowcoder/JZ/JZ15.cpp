static const auto _ =[](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 迭代

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* cur = head;  // 当前指针
        ListNode* pre = nullptr;  // 反转后的头指针
        while(cur != nullptr){
            ListNode* nt = cur -> next;  // 记录下一步
            cur -> next = pre;
            pre = cur;
            cur = nt;
        }
        return pre;
    }
};

// 迭代升级进化版
// 不太好理解，但是非常简洁，考验代码功底

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *p;
        for(p = nullptr; head; swap(head,p))
            swap(p, head->next);
        return p;
    }
};

// 递归
// 递归版本稍微复杂一些，其关键在于反向工作。假设列表的其余部分已经被反转，现在该如何反转它前面的部分？
// 假设列表为：
// n(1) → ... → n(k-1) → n(k) → n(k+1) → ... → n(m) → NULL
// 若从节点 n(k+1) 到 n(m) 已经被反转，正处于 n(k):
// n(1) → ... → n(k-1) → n(k) → n(k+1) ← ... ← n(m)
// 希望 n(k+1) 的下一个节点指向 n(k)
// 所以，n(k) -> next -> next = n(k)
// 要小心的是 n(1) 的下一个必须指向 Ø 。
// 如果忽略了这一点，链表中可能会产生循环。如果使用大小为 2 的链表测试代码，则可能会捕获此错误。

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr || head -> next == nullptr) return head;
        ListNode* p = reverseList(head -> next);
        head -> next -> next = head;
        head -> next = nullptr;
        return p;
    }
};