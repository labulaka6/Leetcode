static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    int kthToLast(ListNode* head, int k) {
        vector<int> tmp;
        int n = 0;
        while(head){
            tmp.emplace_back(head->val);
            head = head->next;
            n++;
        }
        return tmp[n-k];
    }
};

// 哈希表

class Solution {
public:
    int kthToLast(ListNode* head, int k) {
        unordered_map<int, int> M;
        int n = 0;
        while(head){
            M[n] = head->val;
            head = head->next;
            n++;
        }
        return M[n-k];
    }
};

// 双指针
// 开始时让两个指针均指向起始位置，然后先让其中一个指针往后走K步
// 然后两个指针同步向后移动直至先走的指针为空(即走到尾端)

class Solution {
public:
    int kthToLast(ListNode* head, int k) {
        ListNode* p = head;
        while(k > 0){
            p = p->next;
            k--;
        }
        while(p){
            head = head->next;
            p = p->next;
        }
        return head->val;
    }
};