#
# @lc app=leetcode id=3347 lang=python3
#
# [3347] Maximum Frequency of an Element After Performing Operations II
#

# @lc code=start
import collections
from typing import List

class Solution:
    def maxFrequency(self, nums: List[int], k: int, numOperations: int) -> int:
        nums.sort()
        n = len(nums)
        
        # Case 1: Target value is not in original nums.
        # Find the maximum number of elements that fit in any window of length 2k.
        # If target y is the center, elements in [y-k, y+k] can be converted to y.
        max_window = 0
        left = 0
        for right in range(n):
            while nums[right] - nums[left] > 2 * k:
                left += 1
            max_window = max(max_window, right - left + 1)
        
        # If target is not in nums, we can change at most numOperations elements.
        ans = min(max_window, numOperations)
        
        # Case 2: Target value is an existing element x in nums.
        counts = collections.Counter(nums)
        unique_elements = sorted(counts.keys())
        
        left_p = 0
        right_p = 0
        for x in unique_elements:
            # Use two pointers to find the number of elements in the range [x-k, x+k]
            while right_p < n and nums[right_p] <= x + k:
                right_p += 1
            while left_p < n and nums[left_p] < x - k:
                left_p += 1
            
            total_in_range = right_p - left_p
            # We have counts[x] already, and can change up to numOperations others in range.
            # This simplifies to min(total_in_range, count(x) + numOperations).
            current_freq = min(total_in_range, counts[x] + numOperations)
            if current_freq > ans:
                ans = current_freq
                
        return ans
# @lc code=end