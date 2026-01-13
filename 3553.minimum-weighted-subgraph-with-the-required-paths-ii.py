#
# @lc app=leetcode id=3553 lang=python3
#
# [3553] Minimum Weighted Subgraph With the Required Paths II
#

from typing import List

# @lc code=start
class Solution:
    def minimumWeight(self, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        n = len(edges) + 1
        adj = [[] for _ in range(n)]
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))

        LOG = n.bit_length()
        parent = [[-1] * n for _ in range(LOG)]
        depth = [0] * n
        dist_root = [0] * n

        # Iterative DFS from root 0
        stack = [(0, -1, 0, 0)]  # (node, par, depth, dist_from_root)
        while stack:
            u, p, dep, d = stack.pop()
            parent[0][u] = p
            depth[u] = dep
            dist_root[u] = d
            for v, w in adj[u]:
                if v == p:
                    continue
                stack.append((v, u, dep + 1, d + w))

        # Build binary lifting table
        for k in range(1, LOG):
            prev = parent[k - 1]
            cur = parent[k]
            for i in range(n):
                mid = prev[i]
                cur[i] = -1 if mid == -1 else prev[mid]

        def lca(u: int, v: int) -> int:
            if depth[u] < depth[v]:
                u, v = v, u
            diff = depth[u] - depth[v]
            bit = 0
            while diff:
                if diff & 1:
                    u = parent[bit][u]
                diff >>= 1
                bit += 1
            if u == v:
                return u
            for k in range(LOG - 1, -1, -1):
                pu, pv = parent[k][u], parent[k][v]
                if pu != pv:
                    u, v = pu, pv
            return parent[0][u]

        def dist(u: int, v: int) -> int:
            w = lca(u, v)
            return dist_root[u] + dist_root[v] - 2 * dist_root[w]

        ans = []
        for a, b, d in queries:
            dab = dist(a, b)
            dad = dist(a, d)
            dbd = dist(b, d)
            ans.append((dab + dad + dbd) // 2)
        return ans
# @lc code=end
