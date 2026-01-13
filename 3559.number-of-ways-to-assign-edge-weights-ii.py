#
# @lc app=leetcode id=3559 lang=python3
#
# [3559] Number of Ways to Assign Edge Weights II
#

from typing import List

# @lc code=start
class Solution:
    def assignEdgeWeights(self, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        MOD = 10**9 + 7
        n = len(edges) + 1

        g = [[] for _ in range(n + 1)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)

        LOG = (n).bit_length()
        parent = [[0] * (n + 1) for _ in range(LOG)]
        depth = [0] * (n + 1)

        # Iterative DFS from root = 1
        stack = [(1, 0)]
        order = [1]
        parent[0][1] = 0
        depth[1] = 0
        while stack:
            node, par = stack.pop()
            parent[0][node] = par
            for nei in g[node]:
                if nei == par:
                    continue
                depth[nei] = depth[node] + 1
                stack.append((nei, node))

        # Build binary lifting table
        for j in range(1, LOG):
            pj = parent[j - 1]
            cur = parent[j]
            for v in range(1, n + 1):
                cur[v] = pj[pj[v]]

        def lca(a: int, b: int) -> int:
            if depth[a] < depth[b]:
                a, b = b, a
            # lift a
            diff = depth[a] - depth[b]
            bit = 0
            while diff:
                if diff & 1:
                    a = parent[bit][a]
                diff >>= 1
                bit += 1
            if a == b:
                return a
            for j in range(LOG - 1, -1, -1):
                if parent[j][a] != parent[j][b]:
                    a = parent[j][a]
                    b = parent[j][b]
            return parent[0][a]

        # Precompute powers of 2
        pow2 = [1] * (n + 1)
        for i in range(1, n + 1):
            pow2[i] = (pow2[i - 1] * 2) % MOD

        ans = []
        for u, v in queries:
            if u == v:
                ans.append(0)
                continue
            w = lca(u, v)
            dist = depth[u] + depth[v] - 2 * depth[w]
            ans.append(pow2[dist - 1])  # dist > 0 here
        return ans
# @lc code=end
