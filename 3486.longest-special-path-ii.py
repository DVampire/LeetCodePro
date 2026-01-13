#
# @lc app=leetcode id=3486 lang=python3
#
# [3486] Longest Special Path II
#

from typing import List

# @lc code=start
class Solution:
    def longestSpecialPath(self, edges: List[List[int]], nums: List[int]) -> List[int]:
        n = len(nums)
        adj = [[] for _ in range(n)]
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))

        maxv = max(nums) if nums else 0
        freq = [0] * (maxv + 1)
        twos = 0
        threes = 0

        path_vals: List[int] = []
        path_dist: List[int] = []

        ops: List[tuple[int, int]] = []  # (val, delta)
        l = 0

        def apply(val: int, delta: int) -> None:
            nonlocal twos, threes
            prev = freq[val]
            new = prev + delta

            if prev == 2:
                twos -= 1
            elif prev == 3:
                threes -= 1

            if new == 2:
                twos += 1
            elif new == 3:
                threes += 1

            freq[val] = new

        def do(val: int, delta: int) -> None:
            apply(val, delta)
            ops.append((val, delta))

        bestLen = -1
        bestNodes = 10**18

        # stack frames:
        # enter: (u, parent, dist, 0)
        # exit : (u, parent, dist, 1, l0, ops_len)
        stack = [(0, -1, 0, 0)]

        while stack:
            frame = stack.pop()
            if frame[3] == 0:
                u, parent, dist, _ = frame
                l0 = l
                ops_len = len(ops)

                # enter node
                path_vals.append(nums[u])
                path_dist.append(dist)
                do(nums[u], +1)

                # shrink until valid
                while threes > 0 or twos > 1:
                    rem_val = path_vals[l]
                    do(rem_val, -1)
                    l += 1

                # evaluate best suffix [l..r]
                curLen = path_dist[-1] - path_dist[l]
                curNodes = len(path_vals) - l
                if curLen > bestLen:
                    bestLen = curLen
                    bestNodes = curNodes
                elif curLen == bestLen and curNodes < bestNodes:
                    bestNodes = curNodes

                # schedule exit then children
                stack.append((u, parent, dist, 1, l0, ops_len))
                for v, w in reversed(adj[u]):
                    if v == parent:
                        continue
                    stack.append((v, u, dist + w, 0))

            else:
                # exit node: rollback to saved state
                _, _, _, _, l0, ops_len = frame
                while len(ops) > ops_len:
                    val, delta = ops.pop()
                    apply(val, -delta)
                l = l0
                path_vals.pop()
                path_dist.pop()

        return [bestLen, bestNodes]
# @lc code=end
