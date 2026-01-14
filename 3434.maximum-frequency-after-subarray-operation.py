#
# @lc app=leetcode id=3434 lang=python3
#
# [3434] Maximum Frequency After Subarray Operation
#

# @lc code=start
class Solution:
    def maxFrequency(self, nums: List[int], k: int) -> int:
        base_count = nums.count(k)
        max_gain = 0
        
        for v in set(nums):
            if v == k:
                continue
            
            # Kadane's algorithm to find max subarray sum
            # +1 for v (becomes k), -1 for k (stops being k), 0 otherwise
            current_sum = 0
            max_sum = 0  # Floor at 0 (we can always choose x=0 for no change)
            for num in nums:
                if num == v:
                    delta = 1
                elif num == k:
                    delta = -1
                else:
                    delta = 0
                current_sum = max(0, current_sum + delta)
                max_sum = max(max_sum, current_sum)
            
            max_gain = max(max_gain, max_sum)
        
        return base_count + max_gain
# @lc code=end