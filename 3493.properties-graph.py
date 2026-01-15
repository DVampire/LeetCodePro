#
# @lc app=leetcode id=3493 lang=python3
#
# [3493] Properties Graph
#

from typing import List
from collections import defaultdict, deque

# @lc code=start
class Solution:
    def numberOfComponents(self, properties: List[List[int]], k: int) -> int:
        n = len(properties)
        # Convert each row to a set of distinct integers
        sets = [set(row) for row in properties]
        # Build adjacency list based on intersect condition
        adj = [[] for _ in range(n)]
        for i in range(n):
            for j in range(i+1, n):
                # Compute intersection size efficiently
                inter = len(sets[i] & sets[j])
                if inter >= k:
                    adj[i].append(j)
                    adj[j].append(i)
        # Count connected components using BFS/DFS
        visited = [False] * n
        components = 0
        for i in range(n):
            if not visited[i]:
                components += 1
                # BFS to mark all nodes in the same component
                q = deque([i])
                visited[i] = True
                while q:
                    u = q.popleft()
                    for v in adj[u]:
                        if not visited[v]:
                            visited[v] = True
                            q.append(v)
        return components
# @lc code=end