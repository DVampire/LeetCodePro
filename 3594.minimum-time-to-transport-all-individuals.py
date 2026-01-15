#
# @lc app=leetcode id=3594 lang=python3
#
# [3594] Minimum Time to Transport All Individuals
#

# @lc code=start
from typing import List
import math
from functools import lru_cache

class Solution:
    def minTime(self, n: int, k: int, m: int, time: List[int], mul: List[float]) -> float:
        # Sort times? Not necessary because we can choose any subset.
        # We'll use bitmask to represent which individuals are on the left side (base camp).
        # Initially all n individuals are on left.
        # Goal: move all to right (destination).
        # State: (left_mask, stage) where stage is current stage index (0..m-1).
        # left_mask: bits set for individuals still on left.
        # We need to consider trips from left to right (forward) and right to left (return).
        # Since n <= 12, we can use DP with memoization.
        
        # Precompute crossing times for any subset of people? But we need max(time[i]) for subset.
        # Since k <= 5, subsets size up to k. We can precompute for all subsets of size up to k.
        # But we also need return trips with one person.
        
        # Let total_mask = (1 << n) - 1.
        total_mask = (1 << n) - 1
        
        # Precompute max_time for each mask? Not needed; we can compute on the fly as n is small.
        
        @lru_cache(None)
        def dp(left_mask, stage):
            if left_mask == 0:
                return 0.0  # All on right
            
            best = float('inf')
            
            # Generate all non-empty subsets of left_mask with size <= k for forward trip.
            sub = left_mask
            while sub:
                if bin(sub).count('1') <= k:
                    # Forward trip with subset sub from left to right.
                    max_t = max(time[i] for i in range(n) if (sub >> i) & 1)
                    forward_time = max_t * mul[stage]
                    new_stage = (stage + int(math.floor(forward_time))) % m
                    new_left_mask = left_mask ^ sub  # remove those who crossed
                    
                    # After forward trip, we might need a return trip if there are still people left on left.
                    if new_left_mask == 0:
                        total = forward_time + dp(new_left_mask, new_stage)
                        best = min(best, total)
                    else:
                        # Need someone from the right to return. The returning person must be among those who just crossed (sub).
                        for ret in range(n):
                            if (sub >> ret) & 1:
                                return_time = time[ret] * mul[new_stage]
                                ret_new_stage = (new_stage + int(math.floor(return_time))) % m
                                total = forward_time + return_time + dp(new_left_mask | (1 << ret), ret_new_stage)
                                best = min(best, total)
                sub = (sub - 1) & left_mask
            
            return best if best != float('inf') else -1.0
        
        ans = dp(total_mask, 0)
        return ans if ans != float('inf') else -1.0
# @lc code=end