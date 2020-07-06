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
    int search(vector<int>& nums, int target) {
        int pos = binary(nums, target);
        if(pos == -1) return 0;
        int count = 0;
        for(int i = pos; i < nums.size(); ++i){
            if(nums[i] == target) count++;
            else break;
        }
        return count;
    }
};

// 两次二分分别查找第一个和最后一个target

class Solution {
    int binary(vector<int>& nums, int target) {  // 二分查找target最后一个位置
        int l = 0, r = nums.size() - 1;
        while(l <= r) {
            int mid = l + (r - l)/2;
            if(nums[mid] <= target) l = mid + 1;
            else r = mid - 1;
        }
        // if(r < 0 || nums[r] != target) return -1;  // 在本题中无需特殊判断
        return r;
    }

public:
    int search(vector<int>& nums, int target) {
        return binary(nums, target) - binary(nums, target - 1);
    }
};

// 两次二分调库

class Solution {
public:
    int search(vector<int>& nums, int target) {
        return upper_bound(nums.begin(), nums.end(), target) - lower_bound(nums.begin(), nums.end(), target);
    }
};