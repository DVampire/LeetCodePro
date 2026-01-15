#
# @lc app=leetcode id=3743 lang=python3
#
# [3743] Maximize Cyclic Partition Score
#

# @lc code=start
from typing import List

class Solution:
    def maximumScore(self, nums: List[int], k: int) -> int:
        n = len(nums)
        if n == 1:
            return 0
        
        # Double the array to handle cyclic nature
        arr = nums + nums
        
        # Precompute ranges for all relevant subarrays
        range_arr = [[0] * (2 * n) for _ in range(2 * n)]
        for i in range(2 * n):
            mn = mx = arr[i]
            for j in range(i, min(i + n, 2 * n)):
                mn = min(mn, arr[j])
                mx = max(mx, arr[j])
                range_arr[i][j] = mx - mn
        
        best = 0
        
        # Try each starting position
        for start in range(n):
            # prev_dp[j] = max score for first j elements with m-1 partitions
            prev_dp = [-1] * (n + 1)
            prev_dp[0] = 0
            
            for m in range(1, k + 1):
                curr_dp = [-1] * (n + 1)
                for j in range(1, n + 1):
                    for i in range(j):
                        if prev_dp[i] >= 0:
                            val = prev_dp[i] + range_arr[start + i][start + j - 1]
                            curr_dp[j] = max(curr_dp[j], val)
                
                if curr_dp[n] >= 0:
                    best = max(best, curr_dp[n])
                
                prev_dp = curr_dp
                
                # Early termination if no valid states
                if all(x < 0 for x in prev_dp):
                    break
        
        return best
# @lc code=end