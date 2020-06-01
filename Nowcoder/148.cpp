static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 归并排序1 - 迭代

class Solution {
    // 切分链表
    ListNode* cut(ListNode* head, int n) {
        auto p = head;
        while (--n && p) {
            p = p->next;
        }

        if (!p) return nullptr;

        auto next = p->next;
        p->next = nullptr;
        return next;
    }

    // 双路归并
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode dummyHead(0);
        auto p = &dummyHead;
        while (l1 && l2) {
            if (l1->val < l2->val) {
                p->next = l1;
                p = l1;
                l1 = l1->next;
            } else {
                p->next = l2;
                p = l2;
                l2 = l2->next;
            }
        }
        p->next = l1 ? l1 : l2;
        return dummyHead.next;
    }
public:
    ListNode* sortList(ListNode* head) {
        ListNode dummyHead(0);
        dummyHead.next = head;
        auto p = head;
        int length = 0;
        while (p) {
            ++length;
            p = p->next;
        }

        for (int size = 1; size < length; size <<= 1) {  // <<= 1 等同于 *= 2
            auto cur = dummyHead.next;
            auto tail = &dummyHead;

            while (cur) {
                auto left = cur;
                auto right = cut(left, size); // left->@->@ right->@->@->@...
                cur = cut(right, size); // left->@->@ right->@->@  cur->@->...

                tail->next = merge(left, right);
                while (tail->next) {
                    tail = tail->next;
                }
            }
        }
        return dummyHead.next;
    }
};

// 归并排序2 - 递归

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode *fast = head->next, *slow = head;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* tmp = slow->next;
        slow->next = nullptr;
        ListNode* left = sortList(head);
        ListNode* right = sortList(tmp);
        ListNode res(0);
        ListNode* h = &res;
        while (left != nullptr && right != nullptr) {
            if (left->val < right->val) {
                h->next = left;
                left = left->next;
            } else {
                h->next = right;
                right = right->next;
            }
            h = h->next;
        }
        h->next = left != nullptr ? left : right;
        return res.next;
    }
};

// 归并排序3 - 迭代展开

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (head == NULL) return NULL;
        ListNode *h = head;
        ListNode *pre, *res, *h1, *h2;
        int length = 0;
        int intv = 1;
        int size1, size2, i;
        while (h) {
            ++length;
            h = h->next;
        }
        res = new ListNode(0);
        res->next = head;
        while (intv < length) {
            pre = res;
            h = res->next;
            while (h) {
                h1 = h;
                // 找到 h2
                for (i= 0; i< intv; i++) {
                    if (h == NULL) break;
                    h = h->next;
                }
                // 停止这一轮的合并，因为 h2== NULL
                if (i< intv) break;
                h2 = h;
                // 找到下一个h1并保存到h中
                for (i= 0; i< intv; i++) {
                    if (h == NULL) break;
                    h = h->next;
                }
                size1 = intv;
                size2 = i;
                // 合并
                while (size1 && size2) {
                    if (h1->val < h2->val) {
                        pre->next = h1;
                        h1 = h1->next;
                        --size1;
                    } else {
                        pre->next = h2;
                        h2 = h2->next;
                        --size2;
                    }
                    pre = pre->next;
                }
                while (size1-- > 0) {
                    pre->next = h1;
                    h1= h1->next;
                    pre = pre->next;
                }
                while (size2-- > 0) {
                    pre->next = h2;
                    h2= h2->next;
                    pre = pre->next;
                }
                pre->next = h;
            }
            intv *= 2;
        }
        return res->next;
    }
};