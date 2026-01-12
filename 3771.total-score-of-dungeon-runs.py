#
# @lc app=leetcode id=3771 lang=python3
#
# [3771] Total Score of Dungeon Runs
#

# @lc code=start
import bisect
from typing import List

class Solution:
    def totalScore(self, hp: int, damage: List[int], requirement: List[int]) -> int:
        n = len(damage)
        # S[i] will store the prefix sum of damage.
        # S[0] = 0, S[1] = damage[0], ..., S[n] = sum(damage[0...n-1])
        S = [0] * (n + 1)
        for i in range(n):
            S[i+1] = S[i] + damage[i]
        
        total_sum = 0
        # For each room k (1-indexed), we want to find starting rooms j (1 to k)
        # such that hp - (S[k] - S[j-1]) >= requirement[k-1].
        # This rearranges to: S[j-1] >= S[k] + requirement[k-1] - hp.
        # Let m = j-1, where m is in {0, ..., k-1}.
        # Since S is strictly increasing, we can find the smallest m using binary search.
        for k in range(1, n + 1):
            xk = S[k] + requirement[k-1] - hp
            # bisect_left returns the leftmost index m where S[m] >= xk.
            # We search within the range [0, k-1].
            m = bisect.bisect_left(S, xk, 0, k)
            # All indices from m to k-1 inclusive satisfy the condition.
            # The count of such indices is (k-1) - m + 1 = k - m.
            total_sum += (k - m)
            
        return total_sum
# @lc code=end