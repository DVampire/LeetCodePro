#
# @lc app=leetcode id=3413 lang=python3
#
# [3413] Maximum Coins From K Consecutive Bags
#

import bisect
from typing import List

# @lc code=start
class Solution:
    def maximumCoins(self, coins: List[List[int]], k: int) -> int:
        coins.sort(key=lambda x: x[0])
        m = len(coins)
        if m == 0:
            return 0
        L = [c[0] for c in coins]
        R = [c[1] for c in coins]
        C = [c[2] for c in coins]
        lens = [R[i] - L[i] + 1 for i in range(m)]
        prefix_val = [0] * (m + 1)
        for i in range(m):
            prefix_val[i + 1] = prefix_val[i] + C[i] * lens[i]

        def get_P(x: int) -> int:
            if x < 1:
                return 0
            i = bisect.bisect_right(L, x) - 1
            if i < 0:
                return 0
            full_before = prefix_val[i]
            overlap = min(x - L[i] + 1, lens[i])
            return full_before + C[i] * overlap

        change_pts = set()
        for i in range(m):
            change_pts.add(L[i])
            change_pts.add(R[i] + 1)

        cand_s = set(change_pts)
        for cp in change_pts:
            cand_s.add(cp - k)

        ans = 0
        for s in cand_s:
            endd = s + k - 1
            left_end = s - 1
            curr = get_P(endd) - get_P(left_end)
            if curr > ans:
                ans = curr
        return ans
# @lc code=end
