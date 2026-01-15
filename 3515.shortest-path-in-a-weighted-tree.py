#
# @lc app=leetcode id=3515 lang=python3
#
# [3515] Shortest Path in a Weighted Tree
#

# @lc code=start
from typing import List

class Solution:
    def treeQueries(self, n: int, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        # Build adjacency list
        adj = [[] for _ in range(n + 1)]
        edge_weight = {}
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))
            edge_weight[(min(u, v), max(u, v))] = w
        
        # Iterative DFS to compute Euler tour and initial distances
        tin = [0] * (n + 1)
        tout = [0] * (n + 1)
        parent = [0] * (n + 1)
        dist = [0] * (n + 1)
        
        timer = 0
        stack = [(1, 0, 0, False)]
        
        while stack:
            u, p, d, processed = stack.pop()
            if processed:
                tout[u] = timer - 1
            else:
                parent[u] = p
                dist[u] = d
                tin[u] = timer
                timer += 1
                stack.append((u, p, d, True))
                for v, w in adj[u]:
                    if v != p:
                        stack.append((v, u, d + w, False))
        
        # BIT for range update, point query
        bit = [0] * (n + 2)
        
        def update(i, delta):
            i += 1
            while i <= n + 1:
                bit[i] += delta
                i += i & (-i)
        
        def query(i):
            i += 1
            s = 0
            while i > 0:
                s += bit[i]
                i -= i & (-i)
            return s
        
        def range_add(l, r, val):
            update(l, val)
            update(r + 1, -val)
        
        result = []
        
        for q in queries:
            if q[0] == 1:
                _, u, v, w_new = q
                if parent[u] == v:
                    child = u
                else:
                    child = v
                
                key = (min(u, v), max(u, v))
                w_old = edge_weight[key]
                delta = w_new - w_old
                edge_weight[key] = w_new
                
                range_add(tin[child], tout[child], delta)
            else:
                _, x = q
                result.append(dist[x] + query(tin[x]))
        
        return result
# @lc code=end