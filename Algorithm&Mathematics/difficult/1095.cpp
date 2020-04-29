static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */

// 二分查找
// 先找山峰坐标
// 然后在左边上升区间找taget，有的话返回，没有的话在右边下降区间查找

class Solution {
    int binary_search(MountainArray &mountain, int target, int l, int r, int key(int)) {
        target = key(target);
        while (l <= r) {
            int mid = (l + r) / 2;
            int cur = key(mountain.get(mid));
            if (cur == target)
                return mid;
            else if (cur < target)
                l = mid + 1;
            else
                r = mid - 1;
        }
        return -1;
    }
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int l = 0, r = mountainArr.length() - 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (mountainArr.get(mid) < mountainArr.get(mid + 1))
                l = mid + 1;
            else
                r = mid;
        }

        int peak = l;
        int index = binary_search(mountainArr, target, 0, peak, [](int x) -> int{return x;});
        if (index != -1)
            return index;
        return binary_search(mountainArr, target, peak + 1, mountainArr.length() - 1, [](int x) -> int{return -x;});
    }
};

// 另一版本

class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int len = mountainArr.length();
        int peek = len/2;
        int left = 0;
        int right = len-1;
        //寻找峰值
        while(left<right){
            peek = (left+right)/2;
            int peekval = mountainArr.get(peek);
            int peekleftval = mountainArr.get(peek-1);
            int peekrightval = mountainArr.get(peek+1);
            if(peekleftval<peekval&&peekrightval<peekval){
                break;
            }else if(peekleftval<peekval&&peekval<peekrightval){
                left = peek;
            }else{
                right = peek;
            }
        }
        //二分查找左侧
        if(mountainArr.get(peek) == target)return peek;
        left = 0;
        right = peek;
        while(left<right){
            int mid = (left+right)/2;
            int val = mountainArr.get(mid);
            if(val == target)return mid;
            if(val<target){
                left = mid+1;
            }else{
                right = mid;
            }
        }
        //二分查找右侧
        left = peek;
        right = len-1;
        if(mountainArr.get(right) == target)return right;
        while(left<right){
            int mid = (left+right)/2;
            int val = mountainArr.get(mid);
            if(val == target)return mid;
            if(val<target){
                right = mid;
            }else{
                left = mid+1;
            }
        }
        return -1;
    }
};