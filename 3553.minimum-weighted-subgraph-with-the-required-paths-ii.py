#
# @lc app=leetcode id=3553 lang=python3
#
# [3553] Minimum Weighted Subgraph With the Required Paths II
#

# @lc code=start
from typing import List
from collections import deque

class Solution:
    def minimumWeight(self, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        n = len(edges) + 1
        adj = [[] for _ in range(n)]
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))
        
        LOG = 18
        parent = [[-1] * n for _ in range(LOG)]
        depth = [0] * n
        
        # BFS to compute depth and parent[0]
        visited = [False] * n
        q = deque([0])
        visited[0] = True
        parent[0][0] = -1
        while q:
            u = q.popleft()
            for v, w in adj[u]:
                if not visited[v]:
                    visited[v] = True
                    depth[v] = depth[u] + w
                    parent[0][v] = u
                    q.append(v)
        
        # Binary lifting
        for k in range(1, LOG):
            for i in range(n):
                if parent[k-1][i] != -1:
                    parent[k][i] = parent[k-1][parent[k-1][i]]
        
        def get_lca(u: int, v: int) -> int:
            if depth[u] > depth[v]:
                u, v = v, u
            # Level v to u's depth
            for k in range(LOG - 1, -1, -1):
                if depth[v] - (1 << k) >= depth[u]:
                    v = parent[k][v]
            if u == v:
                return u
            # Jump both
            for k in range(LOG - 1, -1, -1):
                if parent[k][u] != parent[k][v]:
                    u = parent[k][u]
                    v = parent[k][v]
            return parent[0][u]
        
        def get_dist(u: int, v: int) -> int:
            l = get_lca(u, v)
            return depth[u] + depth[v] - 2 * depth[l]
        
        ans = []
        for a, b, c in queries:
            d1 = get_dist(a, c)
            d2 = get_dist(b, c)
            d3 = get_dist(a, b)
            ans.append((d1 + d2 + d3) // 2)
        return ans
# @lc code=end