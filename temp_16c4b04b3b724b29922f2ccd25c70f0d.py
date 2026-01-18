#
# @lc app=leetcode id=3356 lang=python3
#
# [3356] Zero Array Transformation II
#

# @lc code=start
from typing import List
from itertools import accumulate

class Solution:
    def minZeroArray(self, nums: List[int], queries: List[List[int]]) -> int:
        n = len(nums)
        nq = len(queries)
        
        def check(k: int) -> bool:
            # If k queries are used, can we make nums a Zero Array?
            # We can if the sum of vali for queries covering each index i is >= nums[i]
            # Use a difference array to calculate the sum of vali over ranges efficiently
            diff = [0] * (n + 1)
            for i in range(k):
                l, r, v = queries[i]
                diff[l] += v
                if r + 1 < n:
                    diff[r + 1] -= v
            
            # Check if total possible decrement at each index is enough
            # accumulate(diff) gives the prefix sums, which are the total decrements
            curr = 0
            for i in range(n):
                curr += diff[i]
                if curr < nums[i]:
                    return False
            return True

        # Binary search for the minimum k in the range [0, nq]
        low, high = 0, nq
        ans = -1
        
        while low <= high:
            mid = (low + high) // 2
            if check(mid):
                ans = mid
                high = mid - 1
            else:
                low = mid + 1
        
        return ans
# @lc code=end