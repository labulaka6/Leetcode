// 双哈希表

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 缓存的节点信息
struct Node {
    int key, val, freq;
    Node(int _key,int _val,int _freq): key(_key), val(_val), freq(_freq){}
};

class LFUCache {
    int minfreq, capacity;
    // key为key的哈希表
    unordered_map<int, list<Node>::iterator> key_table;
    // 频率为key的哈希表，每次在插入均在链表首部，删除均在链表尾部，保证与时序一致
    unordered_map<int, list<Node>> freq_table;
public:
    LFUCache(int _capacity) {
        minfreq = 0;  // 最小频率初始化为0
        capacity = _capacity;  // 缓存大小
        key_table.clear();  // 哈希表置空
        freq_table.clear();  // 哈希表置空
    }

    int get(int key) {
        if (capacity == 0) return -1;
        auto it = key_table.find(key);
        if (it == key_table.end()) return -1;
        list<Node>::iterator node = it -> second;
        int val = node -> val, freq = node -> freq;
        freq_table[freq].erase(node);  // 删除当前freq链表中的node
        // 如果当前链表为空，需要在哈希表中删除，且更新minFreq
        if (freq_table[freq].size() == 0) {
            freq_table.erase(freq);
            if (minfreq == freq) minfreq += 1;
        }
        // 插入到 freq + 1 中
        freq_table[freq + 1].push_front(Node(key, val, freq + 1));
        key_table[key] = freq_table[freq + 1].begin();
        return val;
    }

    void put(int key, int value) {
        if (capacity == 0) return;
        auto it = key_table.find(key);
        if (it == key_table.end()) {
            // 缓存已满，需要进行删除操作
            if (key_table.size() == capacity) {
                // 通过 minFreq 拿到 freq_table[minFreq] 链表的末尾节点
                auto it2 = freq_table[minfreq].back();
                key_table.erase(it2.key);
                freq_table[minfreq].pop_back();
                if (freq_table[minfreq].size() == 0) {
                    freq_table.erase(minfreq);
                }
            }
            freq_table[1].push_front(Node(key, value, 1));
            key_table[key] = freq_table[1].begin();
            minfreq = 1;
        } else {
            // 与 get 操作基本一致，除了需要更新缓存的值
            list<Node>::iterator node = it -> second;
            int freq = node -> freq;
            freq_table[freq].erase(node);
            if (freq_table[freq].size() == 0) {
                freq_table.erase(freq);
                if (minfreq == freq) minfreq += 1;
            }
            freq_table[freq + 1].push_front(Node(key, value, freq + 1));
            key_table[key] = freq_table[freq + 1].begin();
        }
    }
};

// 哈希表 + 平衡二叉树

// 比较直观的想法就是用哈希表 key_table 以键 key 为索引存储缓存，
// 建立一个平衡二叉树 S 来保持缓存根据 (cnt，time) 双关键字由于。
// 在 C++ 中，可以使用 STL 提供的 std::set 类，set 背后的实现是红黑树：
// 对于 get(key) 操作，只要查看一下哈希表 key_table 是否有 key 这个键即可，
// 有的话需要同时更新哈希表和集合中该缓存的使用频率以及使用时间，否则返回 -1。

// 对于 put(key, value) 操作，首先需要查看 key_table 中是否已有对应的键值。
// 如果有的话操作基本等同于 get(key)，不同的是需要更新缓存的 value 值。
// 如果没有的话相当于是新插入一个缓存，这时候需要先查看是否达到缓存容量 capacity，
// 如果达到了的话，需要删除最近最少使用的缓存，即平衡二叉树中最左边的结点，
// 同时删除 key_table 中对应的索引，最后向 key_table 和 S 插入新的缓存信息即可。

struct Node {
    // cnt 表示缓存使用的频率，time 表示缓存的使用时间，key 和 value 表示缓存的键值。
    int cnt, time, key, value;

    Node(int _cnt, int _time, int _key, int _value):cnt(_cnt), time(_time), key(_key), value(_value){}
    // 重载 < 运算符实现一个 Node 类的比较函数，用于生成平衡二叉树
    // 将 cnt（使用频率）作为第一关键字，time（最近一次使用的时间）作为第二关键字
    bool operator < (const Node& rhs) const {
        return cnt == rhs.cnt ? time < rhs.time : cnt < rhs.cnt;
    }
};

class LFUCache {
    int capacity, time;  // 缓存容量，时间戳
    unordered_map<int, Node> key_table;
    set<Node> S;
public:
    LFUCache(int _capacity) {
        capacity = _capacity;
        time = 0;
        key_table.clear();
        S.clear();
    }

    int get(int key) {
        if (capacity == 0) return -1;
        auto it = key_table.find(key);
        if (it == key_table.end()) return -1;  // 如果哈希表中没有键 key，返回 -1
        Node cache = it -> second;  // 从哈希表中得到旧的缓存
        S.erase(cache);  // 从平衡二叉树中删除旧的缓存
        cache.cnt += 1;  // 将旧缓存更新
        cache.time = ++time;  // 将旧缓存更新
        S.insert(cache);  // 将新缓存重新放入哈希表和平衡二叉树中
        it -> second = cache;
        return cache.value;
    }

    void put(int key, int value) {
        if (capacity == 0) return;
        auto it = key_table.find(key);
        if (it == key_table.end()) {
            // 如果到达缓存容量上限
            if (key_table.size() == capacity) {
                // 从哈希表和平衡二叉树中删除最近最少使用的缓存
                key_table.erase(S.begin() -> key);
                S.erase(S.begin());
            }
            // 创建新的缓存
            Node cache = Node(1, ++time, key, value);
            // 将新缓存放入哈希表和平衡二叉树中
            key_table.insert(make_pair(key, cache));
            S.insert(cache);
        }
        else {
            // 这里和 get() 函数类似
            Node cache = it -> second;
            S.erase(cache);
            cache.cnt += 1;
            cache.time = ++time;
            cache.value = value;
            S.insert(cache);
            it -> second = cache;
        }
    }
};