#
# @lc app=leetcode id=3419 lang=python3
#
# [3419] Minimize the Maximum Edge Weight of Graph
#

# @lc code=start
from typing import List
from collections import deque

class Solution:
    def minMaxWeight(self, n: int, edges: List[List[int]], threshold: int) -> int:
        def can_reach(M: int) -> bool:
            adj = [[] for _ in range(n)]
            for a, b, w in edges:
                if w <= M:
                    adj[b].append(a)  # reverse edge b -> a
            visited = [False] * n
            q = deque([0])
            visited[0] = True
            count = 1
            while q:
                u = q.popleft()
                for v in adj[u]:
                    if not visited[v]:
                        visited[v] = True
                        count += 1
                        q.append(v)
            return count == n
        
        left, right = 0, 1000001
        ans = -1
        while left <= right:
            mid = left + (right - left) // 2
            if can_reach(mid):
                ans = mid
                right = mid - 1
            else:
                left = mid + 1
        return ans
# @lc code=end