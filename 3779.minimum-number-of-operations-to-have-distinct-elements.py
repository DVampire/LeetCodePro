#
# @lc app=leetcode id=3779 lang=python3
#
# [3779] Minimum Number of Operations to Have Distinct Elements
#

# @lc code=start
class Solution:
    def minOperations(self, nums: List[int]) -> int:
        n = len(nums)
        seen = set()
        last_bad_idx = -1
        
        # Find the largest index i such that nums[i:] contains a duplicate.
        # This is equivalent to finding the rightmost index i that has a duplicate at some j > i.
        for i in range(n - 1, -1, -1):
            if nums[i] in seen:
                last_bad_idx = i
                break
            seen.add(nums[i])
        
        # If no duplicates were found in the entire array, 0 operations are needed.
        if last_bad_idx == -1:
            return 0
        
        # We must remove elements at least until the suffix starting index is greater than last_bad_idx.
        # The suffix starts at index 3 * k after k operations.
        # We need 3 * k >= last_bad_idx + 1.
        # k = ceil((last_bad_idx + 1) / 3)
        return (last_bad_idx + 3) // 3
# @lc code=end