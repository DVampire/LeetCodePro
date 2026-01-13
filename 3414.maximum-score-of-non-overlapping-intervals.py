#
# @lc app=leetcode id=3414 lang=python3
#
# [3414] Maximum Score of Non-overlapping Intervals
#

from typing import List, Tuple
import bisect

# @lc code=start
class Solution:
    def maximumWeight(self, intervals: List[List[int]]) -> List[int]:
        n = len(intervals)
        K = 4

        # Sort by end time; keep (l, r, w, original_index)
        arr = [(l, r, w, idx) for idx, (l, r, w) in enumerate(intervals)]
        arr.sort(key=lambda x: (x[1], x[0], x[3]))

        # 1-indexed for DP convenience
        starts = [0] * (n + 1)
        ends = [-(10**30)] * (n + 1)  # dummy at 0
        weights = [0] * (n + 1)
        orig = [0] * (n + 1)
        for i in range(1, n + 1):
            l, r, w, idx = arr[i - 1]
            starts[i] = l
            ends[i] = r
            weights[i] = w
            orig[i] = idx

        # prev[i] = max j < i with ends[j] < starts[i]
        prev = [0] * (n + 1)
        for i in range(1, n + 1):
            # first position with end >= starts[i]
            pos = bisect.bisect_left(ends, starts[i], 1, n + 1)
            prev[i] = pos - 1  # could be 0

        def insert_sorted(tup: Tuple[int, ...], x: int) -> Tuple[int, ...]:
            # keep indices sorted ascending to minimize lexicographically
            p = bisect.bisect_left(tup, x)
            return tup[:p] + (x,) + tup[p:]

        def better(w1: int, c1: Tuple[int, ...], w2: int, c2: Tuple[int, ...]) -> Tuple[int, Tuple[int, ...]]:
            # Return the better of (w1,c1) vs (w2,c2)
            if w1 != w2:
                return (w1, c1) if w1 > w2 else (w2, c2)
            return (w1, c1) if c1 < c2 else (w2, c2)

        # dpW[t][i], dpC[t][i]
        dpW = [[0] * (n + 1) for _ in range(K + 1)]
        dpC = [[() for _ in range(n + 1)] for _ in range(K + 1)]

        for t in range(1, K + 1):
            for i in range(1, n + 1):
                # skip
                sw, sc = dpW[t][i - 1], dpC[t][i - 1]
                # take
                j = prev[i]
                tw = dpW[t - 1][j] + weights[i]
                tc = insert_sorted(dpC[t - 1][j], orig[i])

                bw, bc = better(sw, sc, tw, tc)
                dpW[t][i], dpC[t][i] = bw, bc

        # Choose best among taking up to 4 intervals
        bestW, bestC = 0, ()
        for t in range(1, K + 1):
            bestW, bestC = better(bestW, bestC, dpW[t][n], dpC[t][n])

        return list(bestC)
# @lc code=end
