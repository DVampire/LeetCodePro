#
# @lc app=leetcode id=3510 lang=cpp
#
# [3510] Minimum Pair Removal to Sort Array II
#
# @lc code=start
class Solution {
public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) return 0;
        
        vector<long long> arr(nums.begin(), nums.end());
        
        auto isSorted = [](const vector<long long>& a) {
            for (size_t i = 1; i < a.size(); i++) {
                if (a[i] < a[i-1]) return false;
            }
            return true;
        };
        
        if (isSorted(arr)) return 0;
        
        int operations = 0;
        
        while (!isSorted(arr)) {
            // Find minimum sum pair (leftmost if tie)
            size_t min_idx = 0;
            long long min_sum = LLONG_MAX;
            
            for (size_t i = 0; i < arr.size() - 1; i++) {
                long long sum = arr[i] + arr[i+1];
                if (sum < min_sum) {
                    min_sum = sum;
                    min_idx = i;
                }
            }
            
            // Merge arr[min_idx] and arr[min_idx+1]
            arr[min_idx] = arr[min_idx] + arr[min_idx + 1];
            arr.erase(arr.begin() + min_idx + 1);
            operations++;
        }
        
        return operations;
    }
};
# @lc code=end