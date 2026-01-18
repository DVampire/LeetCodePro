#
# @lc app=leetcode id=3347 lang=python3
#
# [3347] Maximum Frequency of an Element After Performing Operations II
#

# @lc code=start
import collections
from bisect import bisect_left, bisect_right

class Solution:
    def maxFrequency(self, nums: List[int], k: int, numOperations: int) -> int:
        nums.sort()
        n = len(nums)
        counts = collections.Counter(nums)
        
        # Case 1: Target value x is one of the existing numbers in nums
        # For each unique value v in nums, we calculate its frequency.
        # Freq(v) = count(v) + min(numOperations, in_range(v) - count(v))
        # where in_range(v) is the count of elements in [v - k, v + k].
        res = 0
        l, r = 0, 0
        unique_nums = sorted(counts.keys())
        
        # We can use two pointers to find in_range for each unique_num
        # since both unique_num - k and unique_num + k are non-decreasing.
        for v in unique_nums:
            while r < n and nums[r] <= v + k:
                r += 1
            while l < n and nums[l] < v - k:
                l += 1
            in_range = r - l
            res = max(res, min(in_range, counts[v] + numOperations))
            
        # Case 2: Target value x is NOT in nums
        # The frequency is min(numOperations, max_overlap_of_intervals)
        # where intervals are [nums[i] - k, nums[i] + k].
        events = []
        for x in nums:
            events.append((x - k, 1))
            events.append((x + k + 1, -1))
        events.sort()
        
        max_overlap = 0
        curr = 0
        for _, val in events:
            curr += val
            max_overlap = max(max_overlap, curr)
            
        res = max(res, min(numOperations, max_overlap))
        
        return res
# @lc code=end