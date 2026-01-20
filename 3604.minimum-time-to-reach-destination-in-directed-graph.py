#
# @lc app=leetcode id=3604 lang=python3
#
# [3604] Minimum Time to Reach Destination in Directed Graph
#

# @lc code=start
from typing import List
import heapq

class Solution:
    def minTime(self, n: int, edges: List[List[int]]) -> int:
        graph = [[] for _ in range(n)]
        for u, v, s, e in edges:
            graph[u].append((v, s, e))
        
        dist = [float('inf')] * n
        dist[0] = 0
        pq = [(0, 0)]  # (time, node)
        
        while pq:
            time, u = heapq.heappop(pq)
            if time > dist[u]:
                continue
            for v, s, e in graph[u]:
                depart = max(time, s)
                if depart <= e:
                    arr = depart + 1
                    if arr < dist[v]:
                        dist[v] = arr
                        heapq.heappush(pq, (arr, v))
        
        return dist[n-1] if dist[n-1] != float('inf') else -1

# @lc code=end