#
# @lc app=leetcode id=3779 lang=python3
#
# [3779] Minimum Number of Operations to Have Distinct Elements
#

# @lc code=start
class Solution:
    def minOperations(self, nums: List[int]) -> int:
        operations = 0
        start = 0
        
        while start < len(nums):
            # Check if remaining elements are all distinct
            remaining = nums[start:]
            if len(remaining) == len(set(remaining)):
                break
            
            # Remove first 3 elements (or all if fewer than 3)
            start += min(3, len(nums) - start)
            operations += 1
        
        return operations
# @lc code=end