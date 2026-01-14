#
# @lc app=leetcode id=3604 lang=python3
#
# [3604] Minimum Time to Reach Destination in Directed Graph
#
# @lc code=start
import heapq
from collections import defaultdict

class Solution:
    def minTime(self, n: int, edges: List[List[int]]) -> int:
        # Build adjacency list
        graph = defaultdict(list)
        for u, v, start, end in edges:
            graph[u].append((v, start, end))
        
        # Dijkstra's algorithm
        visited = set()
        pq = [(0, 0)]  # (time, node)
        
        while pq:
            time, node = heapq.heappop(pq)
            
            if node in visited:
                continue
            
            visited.add(node)
            
            if node == n - 1:
                return time
            
            for neighbor, start, end in graph[node]:
                if neighbor in visited:
                    continue
                
                if time <= end:
                    if time >= start:
                        arrival_time = time + 1
                    else:
                        arrival_time = start + 1
                    heapq.heappush(pq, (arrival_time, neighbor))
        
        return -1
# @lc code=end