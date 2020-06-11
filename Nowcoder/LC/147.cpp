static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 直观解法

class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        if(NULL == head) return NULL;
        ListNode* complete = head;  // 排好序的部分
        ListNode* execute  = head->next;  // 还未排序的部分
        complete->next = NULL;
        if(NULL == execute) return complete;  // 只有一个节点
        while(execute){
            ListNode* node = execute;  // 本次需要插入排序的节点
            execute = execute->next;  // 将本次排序的节点从还未排序的部分删除
            ListNode* prev = NULL;  // 进行比较的前一个位置，为了方便节点插入的操作
            ListNode* next = complete;  // 进行比较的位置
            while(next && next->val < node->val){  // 寻找合适的位置(若要求稳定的排序算法，则此处应为<=)
                prev = next;
                next = next->next;
            }
            // 插入操作
            if(prev)
                prev->next = node;
            else
                complete = node;
            node->next = next;
        };
        return complete;
    }
};

// 优化
// 题解中有使用 Tail 指针进行提速，但这种情况只适用测试用例正好最大的在后面的情况，概率上来说发生的可能性是很小的。
// 可以可以利用前一个插入的位置进行提速，即每次先把当前要插入的元素和前一个插入点比较，
// 如果比它大，那么就从这里开始搜索，否则才需要从链表头开始搜索。

class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        if(NULL == head) return NULL;
        ListNode* complete = head;  // 排好序的部分
        ListNode* execute  = head->next;  // 还未排序的部分
        complete->next = NULL;
        if(NULL == execute) return complete;  // 只有一个节点
        ListNode* pre = complete;  // 记录上一个插入点
        while(execute){
            ListNode* node = execute;  // 本次需要插入排序的节点
            execute = execute->next;  // 将本次排序的节点从还未排序的部分删除
            ListNode* prev = NULL;  // 进行比较的前一个位置，为了方便节点插入的操作
            ListNode* next = complete;  // 进行比较的位置
            if(pre->val < node->val){
                prev = pre;
                next = pre->next;
            }
            while(next && next->val < node->val){  // 寻找合适的位置(若要求稳定的排序算法，则此处应为<=)
                prev = next;
                next = next->next;
            }
            // 插入操作
            if(prev)
                prev->next = node;
            else
                complete = node;
            node->next = next;
            pre = node;
        };
        return complete;
    }
};