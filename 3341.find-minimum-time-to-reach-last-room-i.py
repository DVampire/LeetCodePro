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
        
        # Priority queue stores (current_time, row, col)
        pq = [(0, 0, 0)]
        
        while pq:
            t, r, c = heapq.heappop(pq)
            
            # If we already found a faster way to this room, skip it
            if t > dist[r][c]:
                continue
                
            # If we reached the target room, return the time
            if r == n - 1 and c == m - 1:
                return t
            
            # Explore all 4 adjacent rooms
            for dr, dc in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                nr, nc = r + dr, c + dc
                
                if 0 <= nr < n and 0 <= nc < m:
                    # The room opens at moveTime[nr][nc]. 
                    # We can start moving at max(current_time, moveTime[nr][nc]).
                    # The move takes exactly 1 second.
                    arrival_time = max(t, moveTime[nr][nc]) + 1
                    
                    if arrival_time < dist[nr][nc]:
                        dist[nr][nc] = arrival_time
                        heapq.heappush(pq, (arrival_time, nr, nc))
                        
        return -1
# @lc code=end