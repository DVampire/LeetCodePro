#
# @lc app=leetcode id=3515 lang=python3
#
# [3515] Shortest Path in a Weighted Tree
#

# @lc code=start
class Solution:
    def treeQueries(self, n: int, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        # Build adjacency list
        adj = [[] for _ in range(n + 1)]
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))
        
        # Iterative DFS to compute in_time, out_time, parent, dist
        in_time = [0] * (n + 1)
        out_time = [0] * (n + 1)
        parent = [0] * (n + 1)
        dist = [0] * (n + 1)
        edge_weight = {}
        
        timer = 0
        stack = [(1, 0, 0, False)]
        
        while stack:
            u, p, d, visited = stack.pop()
            if visited:
                out_time[u] = timer
            else:
                timer += 1
                in_time[u] = timer
                parent[u] = p
                dist[u] = d
                stack.append((u, p, d, True))
                for v, w in adj[u]:
                    if v != p:
                        edge_weight[(u, v)] = w
                        stack.append((v, u, d + w, False))
        
        # BIT for range update and point query
        bit = [0] * (n + 2)
        
        def add(i, delta):
            while i <= n:
                bit[i] += delta
                i += i & (-i)
        
        def query(i):
            s = 0
            while i > 0:
                s += bit[i]
                i -= i & (-i)
            return s
        
        def range_add(l, r, delta):
            add(l, delta)
            add(r + 1, -delta)
        
        # Process queries
        result = []
        for q in queries:
            if q[0] == 1:
                _, u, v, w_new = q
                if parent[v] == u:
                    child = v
                    key = (u, v)
                else:
                    child = u
                    key = (v, u)
                w_old = edge_weight[key]
                delta = w_new - w_old
                edge_weight[key] = w_new
                range_add(in_time[child], out_time[child], delta)
            else:
                _, x = q
                result.append(dist[x] + query(in_time[x]))
        
        return result
# @lc code=end