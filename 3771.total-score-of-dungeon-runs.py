#
# @lc app=leetcode id=3771 lang=python3
#
# [3771] Total Score of Dungeon Runs
#

# @lc code=start
from typing import List
import bisect

class Solution:
    def totalScore(self, hp: int, damage: List[int], requirement: List[int]) -> int:
        n = len(damage)
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] + damage[i]
        total = 0
        for k in range(n):
            thresh = prefix[k + 1] - hp + requirement[k]
            j0 = bisect.bisect_left(prefix, thresh, 0, k + 1)
            total += max(0, k - j0 + 1)
        return total

# @lc code=end
