#
# @lc app=leetcode id=3449 lang=python3
#
# [3449] Maximize the Minimum Game Score
#

# @lc code=start
from typing import List

class Solution:
    def maxScore(self, points: List[int], m: int) -> int:
        n = len(points)
        
        def canAchieve(target: int) -> bool:
            if target == 0:
                return True
            
            moves = 1  # Initial move from -1 to 0
            carry = 1  # Visits at current position
            
            for i in range(n):
                need_i = (target + points[i] - 1) // points[i]  # ceil(target / points[i])
                short = max(need_i - carry, 0)
                
                if i < n - 1:
                    # Oscillate with next position
                    moves += 2 * short
                    next_carry = short
                    need_next = (target + points[i + 1] - 1) // points[i + 1]
                    
                    # Decide whether to move forward
                    if i + 1 < n - 1 or next_carry < need_next:
                        moves += 1
                        next_carry += 1
                    
                    carry = next_carry
                else:
                    # Last position: oscillate with previous position
                    moves += 2 * short
                
                if moves > m:
                    return False
            
            return True
        
        lo, hi = 0, max(points) * m
        while lo < hi:
            mid = (lo + hi + 1) // 2
            if canAchieve(mid):
                lo = mid
            else:
                hi = mid - 1
        
        return lo
# @lc code=end