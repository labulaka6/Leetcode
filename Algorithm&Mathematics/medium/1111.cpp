// 用模拟栈进行括号匹配

// 只要在遍历过程中，保证栈内一半的括号属于序列 A，一半的括号属于序列 B，
// 那么就能保证拆分后最大的嵌套深度最小，是当前最大嵌套深度的一半。
// 要实现这样的对半分配，我们只需要把奇数层的 ( 分配给 A，偶数层的 ( 分配给 B 即可。

// 此外，由于在这个问题中，栈中只会存放 (，因此不需要维护一个真正的栈，只需要用一个变量模拟记录栈的大小。


static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        int d = 0;  // 记录嵌套深度即模拟栈的高度
        vector<int> ans;
        for (char& c : seq)  // 奇数偶数分配给不同序列
            if (c == '(') {
                ++d;
                ans.push_back(d % 2);
            }
            else {
                ans.push_back(d % 2);
                --d;
            }
        return ans;
    }
};

// 找规律

// 对于字符串中的任意一个左括号 (，它的下标编号为 x，嵌套深度为 y。
// 如果它之有 l 个左括号和 r 个右括号，那么根据嵌套深度的定义，有：
// y = l - r + 1
// 下标编号与 l 和 r 的关系也可以直接得到，注意下标编号从 0 开始：
// x = l + r
// 由于 l - r 和 l + r 同奇偶，因此 l - r + 1（即 y）和 l + r（即 x）的奇偶性相反。

// 对于字符串中的任意一个右括号 )，它的下标编号为 x，嵌套深度为 y。
// 如果它之有 l 个左括号和 r 个右括号，那么根据嵌套深度的定义，有：
// y = l - r
// 下标编号与 l 和 r 的关系也可以直接得到，注意下标编号从 0 开始：
// x = l + r
// 因此 y 和 x 的奇偶性相同。

// 这样一来，只需要根据每个位置是哪一种括号以及该位置的下标编号，就能确定将对应的对应的括号分到哪个组了。

class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        vector<int> ans;
        for (int i = 0; i < seq.size(); ++i) {
            // i & 1 应该是 &(且)最后一位,i为奇是1,i为偶是0
            // ^为异或
            // 下面这句的意思是 i为奇数且(则1,i为奇数且)为0;i为偶数且(则1;i为偶数且)则0
            ans.push_back(i & 1 ^ (seq[i] == '('));
            // if(ch == '(')
            //     ans.push_back(i % 2);
            // else
            //     ans.push_back(1 - i % 2);
        }
        return ans;
    }
};