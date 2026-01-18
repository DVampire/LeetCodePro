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
        # Sort the array to use two pointers and binary search efficiently
        nums.sort()
        n = len(nums)
        
        # Case 1: Target value x is not necessarily in nums.
        # The maximum number of elements that can be converted to x is the maximum
        # number of elements that fall within any window of size 2k.
        # This is because if nums[i] and nums[j] are in [x-k, x+k], then nums[j] - nums[i] <= 2k.
        max_overlap = 0
        right = 0
        for left in range(n):
            while right < n and nums[right] - nums[left] <= 2 * k:
                right += 1
            # The window is nums[left...right-1], so size is right - left
            max_overlap = max(max_overlap, right - left)
        
        # If x is not in nums, count(x) = 0. The frequency is min(numOperations, N(x)).
        ans = min(numOperations, max_overlap)
        
        # Case 2: Target value x is one of the values in nums.
        # The frequency is count(x) + min(numOperations, N(x) - count(x)),
        # which simplifies to min(count(x) + numOperations, N(x)).
        counts = collections.Counter(nums)
        unique_vals = sorted(counts.keys())
        
        # Use two pointers to find N(v) for each unique value v in nums
        l_ptr = 0
        r_ptr = 0
        for v in unique_vals:
            # Elements in range [v - k, v + k]
            while l_ptr < n and nums[l_ptr] < v - k:
                l_ptr += 1
            while r_ptr < n and nums[r_ptr] <= v + k:
                r_ptr += 1
            
            n_v = r_ptr - l_ptr
            c = counts[v]
            ans = max(ans, min(c + numOperations, n_v))
            
        return ans
# @lc code=end