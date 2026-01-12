#
# @lc app=leetcode id=3341 lang=python3
#
# [3341] Find Minimum Time to Reach Last Room I
#

# @lc code=start
import heapq
from typing import List

class Solution:
    def minTimeToReach(self, moveTime: List[List[int]]) -> int:
        n = len(moveTime)
        m = len(moveTime[0])
        
        # dist[r][c] will store the minimum time to reach room (r, c)
        dist = [[float('inf')] * m for _ in range(n)]
        dist[0][0] = 0
        
        # Priority queue stores (time, row, col)
        pq = [(0, 0, 0)]
        
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        
        while pq:
            t, r, c = heapq.heappop(pq)
            
            # If we reached the destination, return the time
            if r == n - 1 and c == m - 1:
                return t
            
            # Standard Dijkstra: if we found a better path already, skip
            if t > dist[r][c]:
                continue
            
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                
                if 0 <= nr < n and 0 <= nc < m:
                    # Time to reach the adjacent room:
                    # Wait until moveTime[nr][nc] is reached, then add 1 second for travel.
                    arrival_time = max(t, moveTime[nr][nc]) + 1
                    
                    if arrival_time < dist[nr][nc]:
                        dist[nr][nc] = arrival_time
                        heapq.heappush(pq, (arrival_time, nr, nc))
        
        return -1
# @lc code=end