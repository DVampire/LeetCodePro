#
# @lc app=leetcode id=3530 lang=python3
#
# [3530] Maximum Profit from Valid Topological Order in DAG
#

# @lc code=start
from typing import List
import heapq

class Solution:
    def maxProfit(self, n: int, edges: List[List[int]], score: List[int]) -> int:
        adj = [[] for _ in range(n)]
        indeg = [0] * n
        for u, v in edges:
            adj[u].append(v)
            indeg[v] += 1
        
        pq = []
        for i in range(n):
            if indeg[i] == 0:
                heapq.heappush(pq, (score[i], i))
        
        profit = 0
        position = 1
        while pq:
            sc, u = heapq.heappop(pq)
            profit += sc * position
            position += 1
            for v in adj[u]:
                indeg[v] -= 1
                if indeg[v] == 0:
                    heapq.heappush(pq, (score[v], v))
        return profit

# @lc code=end