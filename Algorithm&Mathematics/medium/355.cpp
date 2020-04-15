// 双哈希表

static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

struct Tweet{
    int tweetId, time;
    Tweet(int _tweetId, int _time):tweetId(_tweetId), time(_time){};
};

class Twitter {
    unordered_map<int, vector<int>> F;  // 用户关注集
    unordered_map<int, vector<Tweet>> T;  // userid - 发的推特
    int time = 0;
public:
    /** Initialize your data structure here. */
    Twitter() {
    }
    
    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        if(F[userId].size() == 0){
            F[userId].emplace_back(userId);
        }
        T[userId].emplace_back(tweetId, time++);
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        vector<Tweet> tem;
        vector<int> ans;
        if(F[userId].size() == 0) return {}; // 用户不存在
        for(int id : F[userId]){
            for(int i = 0; i < T[id].size(); ++i){
                tem.emplace_back(T[id][i]);
            }
        }
        sort(tem.begin(), tem.end(), [](auto &a, auto &b){return a.time > b.time;});
        for(int i = 0; i < 10 && i < tem.size(); ++i){  // 取最近10条Twitter
            ans.emplace_back(tem[i].tweetId);
        }
        return ans;

    }
    
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        if(F[followerId].size() == 0){
            F[followerId].emplace_back(followerId);
        }
        if(followerId == followeeId) return;  // 不能关注自己（因为已经关注过了）
        auto it = find(F[followerId].begin(), F[followerId].end(), followeeId);
        if(it != F[followerId].end()) return;  // 不能关注一个人多次
        F[followerId].emplace_back(followeeId);
    }
    
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        if(followerId == followeeId) return;  // 不能取关自己
        auto it = find(F[followerId].begin(), F[followerId].end(), followeeId);
        if(it != F[followerId].end()) F[followerId].erase(it);  // 只有关注过才能取关
    }
};


// 哈希表 + 链表

class Twitter {
    struct Node{
        // 哈希表存储关注人的 Id
        unordered_set<int> followee;
        // 用链表存储 tweetId
        list<int> tweet;
    };
    // getNewsFeed 检索的推文的上限以及 tweetId 的时间戳
    int recentMax, time;
    // tweetId 对应发送的时间
    unordered_map<int, int> tweetTime;
    // 每个用户存储的信息
    unordered_map<int, Node> user;
public:
    Twitter() {
        time = 0;
        recentMax = 10;
        user.clear();
    }
    
    // 初始化
    void init(int userId) {
        user[userId].followee.clear();
        user[userId].tweet.clear();
    }

    void postTweet(int userId, int tweetId) {
        if (user.find(userId) == user.end()) {
            init(userId);
        }
        // 达到限制，剔除链表末尾元素
        if (user[userId].tweet.size() == recentMax) {
            user[userId].tweet.pop_back();
        }
        user[userId].tweet.push_front(tweetId);
        tweetTime[tweetId] = ++time;
    }
    
    vector<int> getNewsFeed(int userId) {
        vector<int> ans;
        ans.clear();
        // 用户本身发的推特
        for (list<int>::iterator it = user[userId].tweet.begin(); it != user[userId].tweet.end(); ++it) {
            ans.emplace_back(*it);
        }
        // 用户关注的用户发的推特
        for (int followeeId: user[userId].followee) {
            if (followeeId == userId) continue; // 可能出现自己关注自己的情况
            vector<int> res;
            res.clear();
            list<int>::iterator it = user[followeeId].tweet.begin();
            int i = 0;
            // 按照发布时间线性归并
            while (i < (int)ans.size() && it != user[followeeId].tweet.end()) {
                if (tweetTime[(*it)] > tweetTime[ans[i]]) {
                    res.emplace_back(*it);
                    ++it;
                } else {
                    res.emplace_back(ans[i]);
                    ++i;
                }
                // 已经找到这两个链表合起来后最近的 recentMax 条推文
                if ((int)res.size() == recentMax) break;
            }
            // (如果有余下部分)合并余下部分
            for (; i < (int)ans.size() && (int)res.size() < recentMax; ++i) res.emplace_back(ans[i]);
            for (; it != user[followeeId].tweet.end() && (int)res.size() < recentMax; ++it) res.emplace_back(*it);
            ans.assign(res.begin(),res.end());
        }
        return ans;
    }
    
    void follow(int followerId, int followeeId) {
        if (user.find(followerId) == user.end()) {
            init(followerId);
        }
        if (user.find(followeeId) == user.end()) {
            init(followeeId);
        }
        user[followerId].followee.insert(followeeId);
    }
    
    void unfollow(int followerId, int followeeId) {
        user[followerId].followee.erase(followeeId);
    }
};