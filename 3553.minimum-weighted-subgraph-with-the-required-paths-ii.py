#
# @lc app=leetcode id=3553 lang=python3
#
# [3553] Minimum Weighted Subgraph With the Required Paths II
#

# @lc code=start
import collections

class Solution:
    def minimumWeight(self, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        n = len(edges) + 1
        adj = [[] for _ in range(n)]
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))
        
        tour = []
        first_occurrence = [-1] * n
        depth = [0] * n
        D = [0] * n
        
        # Iterative DFS for Euler Tour
        stack = [(0, 0)]  # node, child_index
        first_occurrence[0] = 0
        tour.append(0)
        depth[0] = 0
        D[0] = 0
        
        while stack:
            u, idx = stack[-1]
            if idx < len(adj[u]):
                v, w = adj[u][idx]
                stack[-1] = (u, idx + 1)
                if first_occurrence[v] == -1:
                    first_occurrence[v] = len(tour)
                    depth[v] = depth[u] + 1
                    D[v] = D[u] + w
                    tour.append(v)
                    stack.append((v, 0))
            else:
                stack.pop()
                if stack:
                    tour.append(stack[-1][0])
        
        m = len(tour)
        K = m.bit_length()
        st = [None] * K
        st[0] = tour
        for i in range(1, K):
            prev = st[i-1]
            curr = [0] * (m - (1 << i) + 1)
            offset = 1 << (i - 1)
            for j in range(m - (1 << i) + 1):
                u, v = prev[j], prev[j + offset]
                curr[j] = u if depth[u] < depth[v] else v
            st[i] = curr
            
        # Precompute logs for O(1) LCA
        logs = [0] * (m + 1)
        for i in range(2, m + 1):
            logs[i] = logs[i >> 1] + 1
            
        def get_lca(u, v):
            l, r = first_occurrence[u], first_occurrence[v]
            if l > r: l, r = r, l
            i = logs[r - l + 1]
            a, b = st[i][l], st[i][r - (1 << i) + 1]
            return a if depth[a] < depth[b] else b
        
        ans = []
        for s1, s2, d in queries:
            l12 = get_lca(s1, s2)
            l1d = get_lca(s1, d)
            l2d = get_lca(s2, d)
            res = D[s1] + D[s2] + D[d] - D[l12] - D[l1d] - D[l2d]
            ans.append(res)
            
        return ans
# @lc code=end