#
# @lc app=leetcode id=3488 lang=python3
#
# [3488] Closest Equal Element Queries
#

# @lc code=start
from typing import List
from collections import defaultdict

class Solution:
    def solveQueries(self, nums: List[int], queries: List[int]) -> List[int]:
        n = len(nums)
        pos = defaultdict(list)
        for i, v in enumerate(nums):
            pos[v].append(i)  # appended in increasing i, so each list is sorted

        dist_at = [-1] * n

        def circ_dist(a: int, b: int) -> int:
            d = abs(a - b)
            return min(d, n - d)

        for indices in pos.values():
            m = len(indices)
            if m == 1:
                continue
            for k, cur in enumerate(indices):
                prev_idx = indices[(k - 1) % m]
                next_idx = indices[(k + 1) % m]
                dist_at[cur] = min(circ_dist(cur, prev_idx), circ_dist(cur, next_idx))

        return [dist_at[q] for q in queries]
# @lc code=end
