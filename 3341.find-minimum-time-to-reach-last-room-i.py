#
# @lc app=leetcode id=3341 lang=python3
#
# [3341] Find Minimum Time to Reach Last Room I
#

# @lc code=start
import heapq

class Solution:
    def minTimeToReach(self, moveTime: List[List[int]]) -> int:
        n = len(moveTime)
        m = len(moveTime[0])
        
        # Priority queue: (time, row, col)
        pq = [(0, 0, 0)]
        
        # visited set
        visited = set()
        
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        
        while pq:
            time, r, c = heapq.heappop(pq)
            
            if (r, c) in visited:
                continue
            
            visited.add((r, c))
            
            if r == n - 1 and c == m - 1:
                return time
            
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                
                if 0 <= nr < n and 0 <= nc < m and (nr, nc) not in visited:
                    new_time = max(time, moveTime[nr][nc]) + 1
                    heapq.heappush(pq, (new_time, nr, nc))
        
        return -1
# @lc code=end