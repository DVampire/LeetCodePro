#
# @lc app=leetcode id=3779 lang=cpp
#
# [3779] Minimum Number of Operations to Have Distinct Elements
#

# @lc code=start
class Solution {
public:
    int minOperations(vector<int>& nums) {
        int operations = 0;
        int start = 0;
        int n = nums.size();
        
        while (start < n) {
            // Check if remaining elements are distinct
            unordered_set<int> seen;
            bool hasDuplicate = false;
            for (int i = start; i < n; i++) {
                if (seen.count(nums[i])) {
                    hasDuplicate = true;
                    break;
                }
                seen.insert(nums[i]);
            }
            
            if (!hasDuplicate) {
                return operations;
            }
            
            // Remove first 3 elements (or all remaining)
            start += min(3, n - start);
            operations++;
        }
        
        return operations;
    }
};
# @lc code=end