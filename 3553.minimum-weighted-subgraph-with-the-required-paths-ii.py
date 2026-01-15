#
# @lc app=leetcode id=3553 lang=python3
#
# [3553] Minimum Weighted Subgraph With the Required Paths II
#

# @lc code=start
class Solution:
    def minimumWeight(self, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        n = len(edges) + 1
        
        # Build adjacency list
        adj = [[] for _ in range(n)]
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))
        
        # Binary lifting for LCA
        LOG = max(1, n.bit_length())
        parent = [[-1] * LOG for _ in range(n)]
        depth_level = [0] * n
        depth_weight = [0] * n
        
        # DFS to compute parent, depth
        stack = [(0, -1, 0, 0)]
        visited = [False] * n
        
        while stack:
            node, par, level, weight = stack.pop()
            if visited[node]:
                continue
            visited[node] = True
            parent[node][0] = par
            depth_level[node] = level
            depth_weight[node] = weight
            
            for neighbor, w in adj[node]:
                if not visited[neighbor]:
                    stack.append((neighbor, node, level + 1, weight + w))
        
        # Build binary lifting table
        for j in range(1, LOG):
            for i in range(n):
                if parent[i][j-1] != -1:
                    parent[i][j] = parent[parent[i][j-1]][j-1]
        
        def lca(a, b):
            if depth_level[a] < depth_level[b]:
                a, b = b, a
            
            diff = depth_level[a] - depth_level[b]
            for j in range(LOG):
                if (diff >> j) & 1:
                    a = parent[a][j]
            
            if a == b:
                return a
            
            for j in range(LOG - 1, -1, -1):
                if parent[a][j] != parent[b][j]:
                    a = parent[a][j]
                    b = parent[b][j]
            
            return parent[a][0]
        
        def dist(a, b):
            l = lca(a, b)
            return depth_weight[a] + depth_weight[b] - 2 * depth_weight[l]
        
        result = []
        for src1, src2, dest in queries:
            d1 = dist(src1, src2)
            d2 = dist(src1, dest)
            d3 = dist(src2, dest)
            result.append((d1 + d2 + d3) // 2)
        
        return result
# @lc code=end