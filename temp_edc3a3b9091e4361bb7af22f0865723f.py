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
        
        # Case 1: Target value X is not necessarily in nums.
        # We want to maximize the number of elements in [X-k, X+k], which is a window of size 2k.
        max_w = 0
        l = 0
        for r in range(n):
            while nums[r] - nums[l] > 2 * k:
                l += 1
            max_w = max(max_w, r - l + 1)
        
        # Best frequency if we pick an X that is not in nums (or not benefiting from its own count)
        ans = min(max_w, numOperations)
        
        # Case 2: Target value X is one of the elements in nums.
        counts = collections.Counter(nums)
        unique_nums = sorted(counts.keys())
        
        # Use two pointers to find the number of elements in [v-k, v+k] for each unique v
        ptr_l = 0
        ptr_r = 0
        for v in unique_nums:
            # Range is [v-k, v+k]
            while ptr_l < n and nums[ptr_l] < v - k:
                ptr_l += 1
            while ptr_r < n and nums[ptr_r] <= v + k:
                ptr_r += 1
            
            total_in_range = ptr_r - ptr_l
            c = counts[v]
            # Frequency = existing elements + elements we can change
            ans = max(ans, c + min(total_in_range - c, numOperations))
            
        return ans
# @lc code=end