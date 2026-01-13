#
# @lc app=leetcode id=3710 lang=python3
#
# [3710] Maximum Partition Factor
#

# @lc code=start
from typing import List
from collections import deque

class Solution:
    def maxPartitionFactor(self, points: List[List[int]]) -> int:
        n = len(points)
        if n == 2:
            return 0

        # Precompute pairwise Manhattan distances
        dist = [[0] * n for _ in range(n)]
        max_d = 0
        for i in range(n):
            xi, yi = points[i]
            for j in range(i + 1, n):
                xj, yj = points[j]
                d = abs(xi - xj) + abs(yi - yj)
                dist[i][j] = d
                dist[j][i] = d
                if d > max_d:
                    max_d = d

        def feasible(D: int) -> bool:
            # Build graph edges where dist < D, then test bipartite.
            adj = [[] for _ in range(n)]
            for i in range(n):
                di = dist[i]
                for j in range(i + 1, n):
                    if di[j] < D:
                        adj[i].append(j)
                        adj[j].append(i)

            color = [0] * n  # 0 uncolored, 1 / -1 are the two groups
            for s in range(n):
                if color[s] != 0:
                    continue
                color[s] = 1
                q = deque([s])
                while q:
                    u = q.popleft()
                    cu = color[u]
                    for v in adj[u]:
                        if color[v] == 0:
                            color[v] = -cu
                            q.append(v)
                        elif color[v] == cu:
                            return False
            return True

        lo, hi = 0, max_d
        while lo < hi:
            mid = (lo + hi + 1) // 2
            if feasible(mid):
                lo = mid
            else:
                hi = mid - 1
        return lo
# @lc code=end
