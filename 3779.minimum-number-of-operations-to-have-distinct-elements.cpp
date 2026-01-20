#
# @lc app=leetcode id=3779 lang=cpp
#
# [3779] Minimum Number of Operations to Have Distinct Elements
#

# @lc code=start
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        vector<bool> seen(100001, false);
        
        for (int i = n - 1; i >= 0; --i) {
            if (seen[nums[i]]) {
                // Duplicate found at index i.
                // We must remove everything from 0 to i.
                // Number of elements to remove is i + 1.
                // Each operation removes 3 elements.
                return (i + 1 + 2) / 3;
            }
            seen[nums[i]] = true;
        }
        
        // If we reach here, no duplicates were found in the entire array.
        return 0;
    }
};
# @lc code=end