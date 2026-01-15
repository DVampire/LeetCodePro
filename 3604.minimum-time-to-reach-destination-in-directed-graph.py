#
# @lc app=leetcode id=3604 lang=python3
#
# [3604] Minimum Time to Reach Destination in Directed Graph
#

# @lc code=start
from collections import defaultdict
import heapq

class Solution:
    def minTime(self, n: int, edges: List[List[int]]) -> int:
        # Build adjacency list
        graph = defaultdict(list)
        for u, v, start, end in edges:
            graph[u].append((v, start, end))
        
        # Dijkstra's algorithm
        dist = [float('inf')] * n
        dist[0] = 0
        pq = [(0, 0)]  # (time, node)
        
        while pq:
            time, node = heapq.heappop(pq)
            
            if time > dist[node]:
                continue
            
            if node == n - 1:
                return time
            
            for v, start, end in graph[node]:
                if time > end:
                    continue
                
                if time >= start:
                    arrival = time + 1
                else:
                    arrival = start + 1
                
                if arrival < dist[v]:
                    dist[v] = arrival
                    heapq.heappush(pq, (arrival, v))
        
        return -1
# @lc code=end