#
# @lc app=leetcode id=3347 lang=python3
#
# [3347] Maximum Frequency of an Element After Performing Operations II
#

# @lc code=start
from collections import Counter
from typing import List

class Solution:
    def maxFrequency(self, nums: List[int], k: int, numOperations: int) -> int:
        # Count initial frequencies
        freq = Counter(nums)
        # Sorted version of nums for two-pointer range counting
        sorted_nums = sorted(nums)
        
        # Candidate target values for x
        # C(x) is max at endpoints of [nums[i]-k, nums[i]+k]
        # F(x) is non-zero at nums[i]
        candidates = set()
        for x in nums:
            candidates.add(x)
            candidates.add(x - k)
            candidates.add(x + k)
            
        # Sort candidates to apply two-pointer approach for C(x)
        sorted_candidates = sorted(list(candidates))
        
        ans = 0
        l = 0
        r = 0
        n = len(sorted_nums)
        
        for x in sorted_candidates:
            # Use two pointers to find the number of elements in [x - k, x + k]
            # l is the first index where sorted_nums[l] >= x - k
            while l < n and sorted_nums[l] < x - k:
                l += 1
            # r is the first index where sorted_nums[r] > x + k
            while r < n and sorted_nums[r] <= x + k:
                r += 1
            
            # C(x) is the count of elements in [x - k, x + k]
            c_x = r - l
            # F(x) is the count of elements already equal to x
            f_x = freq.get(x, 0)
            
            # Result for this specific target x:
            # We keep f_x elements and change up to numOperations from the remaining (c_x - f_x)
            # res = f_x + min(numOperations, c_x - f_x) which is min(f_x + numOperations, c_x)
            current_res = min(f_x + numOperations, c_x)
            
            if current_res > ans:
                ans = current_res
                
        return ans
# @lc code=end