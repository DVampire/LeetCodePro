#
# @lc app=leetcode id=3347 lang=python3
#
# [3347] Maximum Frequency of an Element After Performing Operations II
#

# @lc code=start
from collections import Counter

class Solution:
    def maxFrequency(self, nums: List[int], k: int, numOperations: int) -> int:
        nums.sort()
        n = len(nums)
        
        # Case 1: The target value x is not necessarily in nums.
        # We want to maximize min(count(x), numOperations).
        # count(x) is maximized when the window [x-k, x+k] (size 2k) covers most elements.
        max_c = 0
        j = 0
        for i in range(n):
            while j < n and nums[j] - nums[i] <= 2 * k:
                j += 1
            if j - i > max_c:
                max_c = j - i
        
        ans = min(max_c, numOperations)
        
        # Case 2: The target value x is one of the elements in nums.
        # We want to maximize min(count(x), freq(x) + numOperations).
        counts = Counter(nums)
        unique_nums = sorted(counts.keys())
        
        # We use two pointers to find count(x) for each unique x in nums.
        # count(x) is the number of elements in [x - k, x + k].
        l = 0
        r = 0
        for x in unique_nums:
            while l < n and nums[l] < x - k:
                l += 1
            while r < n and nums[r] <= x + k:
                r += 1
            
            c = r - l
            f = counts[x]
            val = min(c, f + numOperations)
            if val > ans:
                ans = val
                
        return ans
# @lc code=end