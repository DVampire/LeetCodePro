#
# @lc app=leetcode id=3538 lang=python3
#
# [3538] Merge Operations for Minimum Travel Time
#
# @lc code=start
class Solution:
    def minTravelTime(self, l: int, n: int, k: int, position: List[int], time: List[int]) -> int:
        from functools import lru_cache
        
        def calculate_travel_time(pos, t):
            total = 0
            for i in range(len(pos) - 1):
                distance = pos[i+1] - pos[i]
                total += distance * t[i]
            return total
        
        @lru_cache(maxsize=None)
        def solve(pos_tuple, time_tuple, merges_remaining):
            pos = list(pos_tuple)
            t = list(time_tuple)
            
            if merges_remaining == 0:
                return calculate_travel_time(pos, t)
            
            n_curr = len(pos)
            min_time = float('inf')
            
            for i in range(1, n_curr - 1):
                new_pos = pos[:i] + pos[i+1:]
                new_time = t[:i] + [t[i] + t[i+1]] + t[i+2:]
                
                result = solve(tuple(new_pos), tuple(new_time), merges_remaining - 1)
                min_time = min(min_time, result)
            
            return min_time
        
        return solve(tuple(position), tuple(time), k)
# @lc code=end