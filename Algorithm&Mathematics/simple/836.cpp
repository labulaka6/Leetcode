// 一般解法 - 检查位置
// 分析在什么情况下，矩形 rec1 和 rec2 没有重叠。
// 想象一下，如果在平面中放置一个固定的矩形 rec2，那么矩形 rec1 必须要出现在 rec2 的「四周」，
// 也就是说，矩形 rec1 需要满足以下四种情况中的至少一种：
// 矩形 rec1 在矩形 rec2 的左侧；
// 矩形 rec1 在矩形 rec2 的右侧；
// 矩形 rec1 在矩形 rec2 的上方；
// 矩形 rec1 在矩形 rec2 的下方。
// 何为「左侧」？如果矩形 rec1 在矩形 rec2 的左侧，那就表示可以找到一条竖直的线（可以与矩形的边重合），
// 使得矩形 rec1 和 rec2 被分在这条竖线的两侧。对于「右侧」、「上方」以及「下方」，它们的定义与「左侧」是类似的。

// 将上述的四种情况翻译成代码。具体地，用 (rec[0], rec[1]) 表示矩形的左下角，
// (rec[2], rec[3]) 表示矩形的右上角，与题目描述一致。
// 对于「左侧」，即矩形 rec1 在 x 轴上的最大值不能大于矩形 rec2 在 x 轴上最小值。
// 对于「右侧」、「上方」以及「下方」同理。因此我们可以翻译成如下的代码：
// 左侧：rec1[2] <= rec2[0]；
// 右侧：rec1[0] >= rec2[2]；
// 上方：rec1[1] >= rec2[3]；
// 下方：rec1[3] <= rec2[1]。

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        return !(rec1[2] <= rec2[0] ||   // left
                 rec1[3] <= rec2[1] ||   // bottom
                 rec1[0] >= rec2[2] ||   // right
                 rec1[1] >= rec2[3]);    // top
    }
};

// 数学解法
// 如果两个矩形重叠，那么它们重叠的区域一定也是一个矩形，
// 那么这代表了两个矩形与 x 轴平行的边（水平边）投影到 x 轴上时会有交集，
// 与 y 轴平行的边（竖直边）投影到 y 轴上时也会有交集。
// 因此，可以将问题看作一维线段是否有交集的问题。

// 矩形 rec1 和 rec2 的水平边投影到 x 轴上的线段分别为 (rec1[0], rec1[2]) 和 (rec2[0], rec2[2])。
// 根据数学知识我们可以知道，当 min(rec1[2], rec2[2]) > max(rec1[0], rec2[0]) 时，这两条线段有交集。
// 对于矩形 rec1 和 rec2 的竖直边投影到 y 轴上的线段，
// 同理可以得到，当 min(rec1[3], rec2[3]) > max(rec1[1], rec2[1]) 时，这两条线段有交集。


class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        return (min(rec1[2], rec2[2]) > max(rec1[0], rec2[0]) &&
                min(rec1[3], rec2[3]) > max(rec1[1], rec2[1]));
    }
};