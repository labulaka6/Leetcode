static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
};

// 拓扑排序
// 「拓扑排序」是「BFS」和「贪心算法」应用于「有向图」的一个专有名词

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        // 每个课程的依赖数目
        unordered_map<int, int> course_prerequisites_count;
        // 课程到其后继课程的映射
        unordered_map<int, vector<int>> prerequisty_to_course;
        for (auto item: prerequisites) {
            int course = item[0];
            int prerequisty = item[1];
            course_prerequisites_count[course]++;
            prerequisty_to_course[prerequisty].push_back(course);
        }

        // 所有无依赖的课程
        queue<int> course_without_prequisty;
        for (int i = 0; i < numCourses; i++) {
            if (course_prerequisites_count.find(i) == course_prerequisites_count.end()) {
                course_without_prequisty.push(i);
            }
        }

        vector<int> result;
        while (!course_without_prequisty.empty()) {
            int temp_course = course_without_prequisty.front();
            course_without_prequisty.pop();
            result.push_back(temp_course);
            // 将该课程的所有后继课程的依赖数减一
            for (auto course: prerequisty_to_course[temp_course]) {
                course_prerequisites_count[course]--;
                // 当该课程的依赖数目为0时，则加入到队列中，并从有依赖的课程中移出
                if (course_prerequisites_count[course] == 0) {
                    course_without_prequisty.push(course);
                    course_prerequisites_count.erase(course);
                }
            }
        }
        // 图中存在环，即不可能完成所有课程
        if (!course_prerequisites_count.empty()) {
            result = {};
        }
        return result;
    }
};