#
# @lc app=leetcode id=3462 lang=python3
#
# [3462] Maximum Sum With at Most K Elements
#

from typing import List

# @lc code=start
class Solution:
    def maxSum(self, grid: List[List[int]], limits: List[int], k: int) -> int:
        if k == 0:
            return 0

        candidates = []
        for row, lim in zip(grid, limits):
            if lim <= 0:
                continue
            # take the largest lim elements from this row
            row_sorted = sorted(row, reverse=True)
            candidates.extend(row_sorted[:lim])

        if not candidates:
            return 0

        candidates.sort(reverse=True)
        return sum(candidates[:k])
# @lc code=end
