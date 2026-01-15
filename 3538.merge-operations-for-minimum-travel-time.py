#
# @lc app=leetcode id=3538 lang=python3
#
# [3538] Merge Operations for Minimum Travel Time
#

# @lc code=start
from functools import cache
from typing import List

class Solution:
    def minTravelTime(self, l: int, n: int, k: int, position: List[int], time: List[int]) -> int:
        # Precompute prefix sums of time
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] + time[i]
        
        def S(a, b):
            # Sum of time[a] to time[b] (inclusive)
            if a > b:
                return 0
            return prefix[b + 1] - prefix[a]
        
        target_kept = n - k
        INF = 10**18
        
        @cache
        def dp(prev, curr, kept):
            # prev: previous kept sign index (-1 if none)
            # curr: current kept sign index
            # kept: number of signs kept so far (including curr)
            
            if kept == target_kept:
                # We've kept enough signs, curr must be n-1
                return 0 if curr == n - 1 else INF
            
            # Remaining signs to add
            remaining_to_add = target_kept - kept
            # next sign must leave room for remaining_to_add - 1 more signs after it
            max_next = n - remaining_to_add
            
            result = INF
            for next_sign in range(curr + 1, max_next + 1):
                # Cost of segment from curr to next_sign
                # Uses accumulated time at curr = sum(time[prev+1], ..., time[curr])
                seg_cost = (position[next_sign] - position[curr]) * S(prev + 1, curr)
                future_cost = dp(curr, next_sign, kept + 1)
                result = min(result, seg_cost + future_cost)
            
            return result
        
        return dp(-1, 0, 1)
        
# @lc code=end