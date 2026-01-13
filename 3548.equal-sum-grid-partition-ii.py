#
# @lc app=leetcode id=3548 lang=python3
#
# [3548] Equal Sum Grid Partition II
#

from typing import List, Dict

# @lc code=start
class Solution:
    def canPartitionGrid(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])

        # Precompute sums and prepare column lists for vertical sweep.
        rowSum = [0] * m
        colSum = [0] * n
        cols = [[] for _ in range(n)]

        total = 0
        overall: Dict[int, int] = {}
        for i in range(m):
            rsum = 0
            row = grid[i]
            for j, v in enumerate(row):
                rsum += v
                colSum[j] += v
                cols[j].append(v)
                total += v
                overall[v] = overall.get(v, 0) + 1
            rowSum[i] = rsum

        def inc(mp: Dict[int, int], x: int, d: int) -> None:
            nv = mp.get(x, 0) + d
            if nv:
                mp[x] = nv
            else:
                mp.pop(x, None)

        def eligible(delta: int, mp: Dict[int, int], r0: int, r1: int, c0: int, c1: int) -> bool:
            h = r1 - r0 + 1
            w = c1 - c0 + 1
            if h * w <= 1:
                return False
            if h == 1 or w == 1:
                # Only endpoints removable in a 1D path.
                if r0 == r1:
                    return delta == grid[r0][c0] or delta == grid[r0][c1]
                else:
                    return delta == grid[r0][c0] or delta == grid[r1][c0]
            # 2D rectangle: any cell removable.
            return mp.get(delta, 0) > 0

        # Horizontal sweep
        top: Dict[int, int] = {}
        bottom: Dict[int, int] = dict(overall)
        topSum = 0

        for r in range(m - 1):  # cut after row r
            for v in grid[r]:
                inc(top, v, 1)
                inc(bottom, v, -1)
            topSum += rowSum[r]
            botSum = total - topSum

            if topSum == botSum:
                return True
            if topSum > botSum:
                delta = topSum - botSum
                if eligible(delta, top, 0, r, 0, n - 1):
                    return True
            else:
                delta = botSum - topSum
                if eligible(delta, bottom, r + 1, m - 1, 0, n - 1):
                    return True

        # Vertical sweep
        left: Dict[int, int] = {}
        right: Dict[int, int] = dict(overall)
        leftSum = 0

        for c in range(n - 1):  # cut after col c
            for v in cols[c]:
                inc(left, v, 1)
                inc(right, v, -1)
            leftSum += colSum[c]
            rightSum = total - leftSum

            if leftSum == rightSum:
                return True
            if leftSum > rightSum:
                delta = leftSum - rightSum
                if eligible(delta, left, 0, m - 1, 0, c):
                    return True
            else:
                delta = rightSum - leftSum
                if eligible(delta, right, 0, m - 1, c + 1, n - 1):
                    return True

        return False
# @lc code=end
