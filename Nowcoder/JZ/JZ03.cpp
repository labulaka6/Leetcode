static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 利用vector的insert()方法

class Solution {
public:
    vector<int> reversePrint(ListNode* head) {
        vector<int> res;
        while(head){
            res.insert(res.begin(), head->val);
            head = head->next;
        }
        return res;
    }
};