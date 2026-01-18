#
# @lc app=leetcode id=3347 lang=python3
#
# [3347] Maximum Frequency of an Element After Performing Operations II
#

# @lc code=start
import bisect
from collections import Counter
from typing import List

class Solution:
    def maxFrequency(self, nums: List[int], k: int, numOperations: int) -> int:
        nums.sort()
        n = len(nums)
        
        # Case 1: Maximize count in any window of size 2k, capped by numOperations
        # This covers the case where the target value x might not be in the original nums.
        max_window_size = 0
        l = 0
        for r in range(n):
            while nums[r] - nums[l] > 2 * k:
                l += 1
            max_window_size = max(max_window_size, r - l + 1)
        
        ans = min(max_window_size, numOperations)
        
        # Case 2: Target value is an existing element in nums
        # We benefit from the existing occurrences of x because they don't consume an operation.
        counts = Counter(nums)
        unique_nums = sorted(counts.keys())
        
        # Use two pointers to find coverage C(x) for each unique x efficiently
        l_ptr = 0
        r_ptr = 0
        for x in unique_nums:
            f_x = counts[x]
            # Find range [x - k, x + k] in sorted nums
            while l_ptr < n and nums[l_ptr] < x - k:
                l_ptr += 1
            while r_ptr < n and nums[r_ptr] <= x + k:
                r_ptr += 1
            
            c_x = r_ptr - l_ptr
            # Frequency = existing count + min(possible changes, allowed operations)
            res = f_x + min(c_x - f_x, numOperations)
            if res > ans:
                ans = res
                    
        return ans
# @lc code=end