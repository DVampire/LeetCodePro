#
# @lc app=leetcode id=3341 lang=python3
#
# [3341] Find Minimum Time to Reach Last Room I
#

# @lc code=start
from typing import List
import heapq

class Solution:
    def minTimeToReach(self, moveTime: List[List[int]]) -> int:
        n = len(moveTime)
        m = len(moveTime[0])
        # Dijkstra's algorithm: (time, i, j)
        pq = []
        heapq.heappush(pq, (0, 0, 0))
        dist = [[float('inf')] * m for _ in range(n)]
        dist[0][0] = 0
        dirs = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        while pq:
            t, i, j = heapq.heappop(pq)
            if i == n-1 and j == m-1:
                return t
            if t > dist[i][j]:
                continue
            for di, dj in dirs:
                ni, nj = i + di, j + dj
                if 0 <= ni < n and 0 <= nj < m:
                    # The earliest time we can enter (ni,nj) is max(t+1, moveTime[ni][nj])
                    nt = max(t + 1, moveTime[ni][nj])
                    if nt < dist[ni][nj]:
                        dist[ni][nj] = nt
                        heapq.heappush(pq, (nt, ni, nj))
        return dist[n-1][m-1]
# @lc code=end