static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 暴力解法1
// 遍历所有链表将数放入数组，排序数组，建立最终的链表
// 时间复杂度O(NlogN) 遍历所有结点O(N),排序算法O(NlogN),创建新链表O(N)
// 空间复杂度O(N) 排序花费O(N),创建新链表花费O(N)

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        vector<int> tem;
        int len = lists.size();
        for(int i = 0; i < len; ++i){
            ListNode* t = lists[i];
            while(t){
                tem.emplace_back(t->val);
                t = t->next;
            }
        }
        int n = tem.size();
        if(n == 0) return nullptr;
        sort(tem.begin(), tem.end());
        ListNode* head = new ListNode(tem[0]);
        ListNode* p = head;
        for(int i = 1; i < n; ++i){
            p->next = new ListNode(tem[i]);
            p = p->next;
        }
        return head;
    }
};

// 暴力解法2
// 还可以每次比较头节点，最小的加到新链表的尾部，然后在原来的链表中去掉这个头结点(head = head->next)
// 时间复杂度O(kN) 比较O(k),N个节点
// 空间复杂度O(N) 创建一个新的链表空间O(N),重复利用O(1)
// 实现较为简单,此处不再赘述

// 顺序合并 - 逐一两两合并链表
// 时间复杂度为 O(k^2 n)
// 空间复杂度为 O(1)

class Solution {
public:
    ListNode* mergeTwoLists(ListNode *a, ListNode *b) {
        if ((!a) || (!b)) return a ? a : b;
        ListNode head, *tail = &head, *aPtr = a, *bPtr = b;
        while (aPtr && bPtr) {
            if (aPtr->val < bPtr->val) {
                tail->next = aPtr;
                aPtr = aPtr->next;
            } else {
                tail->next = bPtr;
                bPtr = bPtr->next;
            }
            tail = tail->next;
        }
        tail->next = (aPtr ? aPtr : bPtr);
        return head.next;
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode *ans = nullptr;
        for (size_t i = 0; i < lists.size(); ++i) {
            ans = mergeTwoLists(ans, lists[i]);
        }
        return ans;
    }
};

// 分治合并 - 递归
// 优化顺序合并
// 每次都两两合并同步进行
// 时间复杂度为 O(kn × logk)
// 空间复杂度为 O(logk)
class Solution {
public:
    ListNode* mergeTwoLists(ListNode *a, ListNode *b) {
        if ((!a) || (!b)) return a ? a : b;
        ListNode head, *tail = &head, *aPtr = a, *bPtr = b;
        while (aPtr && bPtr) {
            if (aPtr->val < bPtr->val) {
                tail->next = aPtr; aPtr = aPtr->next;
            } else {
                tail->next = bPtr; bPtr = bPtr->next;
            }
            tail = tail->next;
        }
        tail->next = (aPtr ? aPtr : bPtr);
        return head.next;
    }

    ListNode* merge(vector <ListNode*> &lists, int l, int r) {
        if (l == r) return lists[l];
        if (l > r) return nullptr;
        int mid = (l + r) >> 1;
        return mergeTwoLists(merge(lists, l, mid), merge(lists, mid + 1, r));
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return merge(lists, 0, lists.size() - 1);
    }
};

// 分治算法 - 循环
// 原地修改
// 时间复杂度O(Nlogk) 合并两个有序列表O(n),将所有合并过程加起来O(Nlogk)
// 空间复杂度O(1)

class Solution {
public:
    ListNode* mergeTwoLists(ListNode *a, ListNode *b) {
        if ((!a) || (!b)) return a ? a : b;
        ListNode head, *tail = &head, *aPtr = a, *bPtr = b;
        while (aPtr && bPtr) {
            if (aPtr->val < bPtr->val) {
                tail->next = aPtr; aPtr = aPtr->next;
            } else {
                tail->next = bPtr; bPtr = bPtr->next;
            }
            tail = tail->next;
        }
        tail->next = (aPtr ? aPtr : bPtr);
        return head.next;
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.size() == 0) return nullptr;
        const int l = lists.size();
        for(int step = 1; step < l; step *= 2)
        {
            for(int i = 0; i < l - step; i += 2*step)
            {
                lists[i] = mergeTwoLists(lists[i], lists[i+step]);
            }
            // 另一种形式
            // for(int i = step; i < l; i += 2*step)
            // {
            //     lists[i-step] = mergeTwoLists(lists[i-step], lists[i]);
            // }
        }
        return lists[0];
    }
};

// 优先队列
// 时间复杂度为 O(kn × logk)
// 优先队列中的元素不超过k个，那么插入和删除的时间代价为O(logk)，
// 这里最多有kn个点，对于每个点都被插入删除各一次，故总的时间代价即渐进时间复杂度为O(kn × logk)。
// 空间复杂度为 O(k)
// 这里用了优先队列，优先队列中的元素不超过k个，故渐进空间复杂度为O(k)

class Solution {
public:
    struct Status {
        int val;
        ListNode *ptr;
        bool operator < (const Status &rhs) const {
            return val > rhs.val;
        }
    };

    priority_queue <Status> q;

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        for (auto node: lists) {
            if (node) q.push({node->val, node});
        }
        ListNode head, *tail = &head;
        while (!q.empty()) {
            auto f = q.top();
            q.pop();
            tail->next = f.ptr;
            tail = tail->next;
            if (f.ptr->next) q.push({f.ptr->next->val, f.ptr->next});
        }
        return head.next;
    }
};