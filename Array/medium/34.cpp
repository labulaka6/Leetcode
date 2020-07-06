static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

// 二分查找

class Solution {
    int binary(vector<int>& nums, int target){  // 二分查找target的第一个位置
        int l = 0, r = nums.size() - 1;
        while(l <= r){
            int mid = l + (r - l)/2;
            if(nums[mid] >= target) r = mid - 1;
            else l = mid + 1;
        }
        if(l >= nums.size() || nums[l] != target) return -1;
        return l;
    }

public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res(2, -1);
        if(nums.size() == 0) return res;
        int pos = binary(nums, target);
        if(pos == -1) return res;
        int tmp = pos;
        for(int i = pos; i < nums.size(); ++i){
            if(nums[i] == target) pos++;
            else break;
        }
        res[0] = tmp;
        res[1] = pos - 1;
        return res;
    }
};

// 两次二分分别查找第一个和最后一个target

class Solution {
    int binaryLeft(vector<int>& nums, int target){  // 二分查找target的第一个位置
        int l = 0, r = nums.size() - 1;
        while(l <= r){
            int mid = l + (r - l)/2;
            if(nums[mid] >= target) r = mid - 1;
            else l = mid + 1;
        }
        if(l >= nums.size() || nums[l] != target) return -1;
        return l;
    }

    int binaryRight(vector<int>& nums, int target) {  // 二分查找target最后一个位置
        int l = 0, r = nums.size() - 1;
        while(l <= r) {
            int mid = l + (r - l)/2;
            if(nums[mid] <= target) l = mid + 1;
            else r = mid - 1;
        }
        if(r < 0 || nums[r] != target) return -1;
        return r;
    }

public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res(2);
        int l = binaryLeft(nums, target);
        int r = binaryRight(nums, target);
        res[0] = l;
        res[1] = r;
        return res;
    }
};