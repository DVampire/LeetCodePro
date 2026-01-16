#
# @lc app=leetcode id=3434 lang=python3
#
# [3434] Maximum Frequency After Subarray Operation
#

# @lc code=start
class Solution:
    def maxFrequency(self, nums: List[int], k: int) -> int:
        n = len(nums)
        max_freq = 1
        
        # Since values are small (1-50), we can try each possible target value
        for target in range(1, 51):
            # Use sliding window to find maximum length subarray that can be made equal to target
            left = 0
            total_operations = 0
            
            for right in range(n):
                # Operations needed to make nums[right] equal to target
                total_operations += abs(nums[right] - target)
                
                # Shrink window if operations exceed k
                while total_operations > k:
                    total_operations -= abs(nums[left] - target)
                    left += 1
                
                # Update maximum frequency
                max_freq = max(max_freq, right - left + 1)
        
        return max_freq
# @lc code=end