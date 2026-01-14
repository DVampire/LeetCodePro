#
# @lc app=leetcode id=3771 lang=python3
#
# [3771] Total Score of Dungeon Runs
#

# @lc code=start
from bisect import bisect_left

class Solution:
    def totalScore(self, hp: int, damage: List[int], requirement: List[int]) -> int:
        n = len(damage)
        
        # Build prefix sum array
        prefix = [0]
        for d in damage:
            prefix.append(prefix[-1] + d)
        
        total = 0
        
        # For each room i
        for i in range(n):
            # Calculate threshold: minimum prefix[j] needed to get a point at room i
            threshold = prefix[i+1] - hp + requirement[i]
            
            # Use binary search to find count of elements >= threshold in prefix[0..i]
            idx = bisect_left(prefix, threshold, 0, i+1)
            count = (i + 1) - idx
            total += count
        
        return total
# @lc code=end