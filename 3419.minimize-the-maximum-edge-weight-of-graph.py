#
# @lc app=leetcode id=3419 lang=python3
#
# [3419] Minimize the Maximum Edge Weight of Graph
#

from typing import List
import heapq
import math

# @lc code=start
class Solution:
    def minMaxWeight(self, n: int, edges: List[List[int]], threshold: int) -> int:
        # Build reversed graph: b -> a with weight w (original a -> b)
        rev = [[] for _ in range(n)]
        for a, b, w in edges:
            rev[b].append((a, w))

        INF = math.inf
        dist = [INF] * n
        dist[0] = 0
        pq = [(0, 0)]  # (bottleneck value to reach 0, node)

        while pq:
            d, v = heapq.heappop(pq)
            if d != dist[v]:
                continue
            for u, w in rev[v]:
                nd = max(d, w)
                if nd < dist[u]:
                    dist[u] = nd
                    heapq.heappush(pq, (nd, u))

        if any(x is INF for x in dist):
            return -1
        return max(dist)
# @lc code=end
