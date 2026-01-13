#
# @lc app=leetcode id=3459 lang=python3
#
# [3459] Length of Longest V-Shaped Diagonal Segment
#

# @lc code=start
from typing import List
from array import array

class Solution:
    def lenOfVDiagonal(self, grid: List[List[int]]) -> int:
        n = len(grid)
        m = len(grid[0])
        size = n * m

        # Directions in clockwise order: NE, SE, SW, NW
        dr = (-1, 1, 1, -1)
        dc = (1, 1, -1, -1)
        # clockwise(d) = (d + 1) % 4

        # dp1_2[d][idx], dp1_0[d][idx]: straight alternating lengths starting at idx
        dp1_2 = [array('H', [0]) * size for _ in range(4)]
        dp1_0 = [array('H', [0]) * size for _ in range(4)]

        # dp0_2[d][idx], dp0_0[d][idx]: alternating lengths with at most one future clockwise turn
        dp0_2 = [array('H', [0]) * size for _ in range(4)]
        dp0_0 = [array('H', [0]) * size for _ in range(4)]

        # Helper to decide traversal order so that (i+dr[d], j+dc[d]) is already processed.
        def ranges_for_direction(d: int):
            ir = range(n - 1, -1, -1) if dr[d] == 1 else range(n)
            jr = range(m - 1, -1, -1) if dc[d] == 1 else range(m)
            return ir, jr

        # Step A: compute dp1 (no turn)
        for d in range(4):
            ir, jr = ranges_for_direction(d)
            drd, dcd = dr[d], dc[d]
            a2 = dp1_2[d]
            a0 = dp1_0[d]
            for i in ir:
                row = grid[i]
                base = i * m
                ni = i + drd
                in_i = 0 <= ni < n
                for j in jr:
                    v = row[j]
                    idx = base + j
                    nj = j + dcd
                    if in_i and 0 <= nj < m:
                        nidx = ni * m + nj
                        if v == 2:
                            a2[idx] = 1 + a0[nidx]
                        elif v == 0:
                            a0[idx] = 1 + a2[nidx]
                        # else remain 0
                    else:
                        if v == 2:
                            a2[idx] = 1
                        elif v == 0:
                            a0[idx] = 1

        # Step B: compute dp0 (one turn allowed)
        for d in range(4):
            ir, jr = ranges_for_direction(d)
            drd, dcd = dr[d], dc[d]
            cw = (d + 1) & 3
            drc, dcc = dr[cw], dc[cw]

            b2 = dp0_2[d]
            b0 = dp0_0[d]

            # For turn option we need dp1 in cw direction
            cw1_2 = dp1_2[cw]
            cw1_0 = dp1_0[cw]

            for i in ir:
                row = grid[i]
                base = i * m

                ni = i + drd
                in_next_i = 0 <= ni < n

                ti = i + drc
                in_turn_i = 0 <= ti < n

                for j in jr:
                    v = row[j]
                    idx = base + j

                    # continue straight
                    cont = 0
                    nj = j + dcd
                    if in_next_i and 0 <= nj < m:
                        nidx = ni * m + nj
                        # cont depends on expected toggle
                        # (filled below based on v)

                    # turn now
                    turn = 0
                    tj = j + dcc
                    if in_turn_i and 0 <= tj < m:
                        tidx = ti * m + tj
                        # turn depends on expected toggle
                        # (filled below based on v)

                    if v == 2:
                        if in_next_i and 0 <= nj < m:
                            cont = b0[nidx]
                        if in_turn_i and 0 <= tj < m:
                            turn = cw1_0[tidx]
                        best = cont if cont >= turn else turn
                        b2[idx] = 1 + best
                    elif v == 0:
                        if in_next_i and 0 <= nj < m:
                            cont = b2[nidx]
                        if in_turn_i and 0 <= tj < m:
                            turn = cw1_2[tidx]
                        best = cont if cont >= turn else turn
                        b0[idx] = 1 + best
                    # else remain 0

        # Step C: evaluate all starts (value 1)
        ans = 0
        for i in range(n):
            row = grid[i]
            base = i * m
            for j in range(m):
                if row[j] != 1:
                    continue
                if ans < 1:
                    ans = 1
                for d in range(4):
                    ni = i + dr[d]
                    nj = j + dc[d]
                    if 0 <= ni < n and 0 <= nj < m:
                        nidx = ni * m + nj
                        cand = 1 + dp0_2[d][nidx]
                        if cand > ans:
                            ans = cand

        return ans
# @lc code=end
