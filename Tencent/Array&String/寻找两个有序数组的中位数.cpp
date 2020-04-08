static const auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    return nullptr;
}();

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size(), cnt = 0;
        int sortArray[m+n];
        int i = 0, j = 0;
        while(i < m && j < n){
            if(nums1[i] <= nums2[j]) sortArray[cnt++] = nums1[i++];
            else sortArray[cnt++] = nums2[j++];
        }
        while(i < m){
            sortArray[cnt++] = nums1[i++];
        }
        while(j < n){
            sortArray[cnt++] = nums2[j++];
        }
        double ans = 0;
        int flag = (m+n)/2;
        if((m+n)%2 == 0){
            ans = (sortArray[flag-1] + sortArray[flag])/2.0;
        }else{
            ans = sortArray[flag];
        }
        return ans;
    }
};