#
# @lc app=leetcode id=3585 lang=python3
#
# [3585] Find Weighted Median Node in Tree
#

from typing import List
from array import array

# @lc code=start
class Solution:
    def findMedian(self, n: int, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        adj = [[] for _ in range(n)]
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))

        LOG = n.bit_length()
        up = [array('i', [-1]) * n for _ in range(LOG)]
        ws = [array('q', [0]) * n for _ in range(LOG)]
        depth = array('i', [0]) * n
        dist = array('q', [0]) * n

        # Iterative DFS to set level 0 parents and distances
        stack = [(0, -1, 0, 0)]  # node, parent, depth, distRoot
        while stack:
            node, par, dep, ds = stack.pop()
            up[0][node] = par
            depth[node] = dep
            dist[node] = ds
            for nei, w in adj[node]:
                if nei == par:
                    continue
                ws[0][nei] = w
                stack.append((nei, node, dep + 1, ds + w))

        # Build binary lifting tables
        for k in range(1, LOG):
            upk = up[k]
            upkm1 = up[k - 1]
            wsk = ws[k]
            wskm1 = ws[k - 1]
            for v in range(n):
                p = upkm1[v]
                if p != -1:
                    upk[v] = upkm1[p]
                    wsk[v] = wskm1[v] + wskm1[p]

        def lca(a: int, b: int) -> int:
            if depth[a] < depth[b]:
                a, b = b, a
            diff = depth[a] - depth[b]
            bit = 0
            while diff:
                if diff & 1:
                    a = up[bit][a]
                diff >>= 1
                bit += 1
            if a == b:
                return a
            for k in range(LOG - 1, -1, -1):
                if up[k][a] != up[k][b]:
                    a = up[k][a]
                    b = up[k][b]
            return up[0][a]

        def first_reach_up(node: int, target: int) -> int:
            # first node on upward path with distance from start >= target
            if target <= 0:
                return node
            cur = node
            acc = 0
            for k in range(LOG - 1, -1, -1):
                p = up[k][cur]
                if p != -1 and acc + ws[k][cur] < target:
                    acc += ws[k][cur]
                    cur = p
            # next step crosses/reaches target
            p0 = up[0][cur]
            return p0 if p0 != -1 else cur

        def climb_with_limit(node: int, limit: int) -> int:
            # climb up from node as far as possible with total climbed weight <= limit
            cur = node
            acc = 0
            for k in range(LOG - 1, -1, -1):
                p = up[k][cur]
                if p != -1 and acc + ws[k][cur] <= limit:
                    acc += ws[k][cur]
                    cur = p
            return cur

        ans = []
        for u, v in queries:
            if u == v:
                ans.append(u)
                continue
            l = lca(u, v)
            du = dist[u] - dist[l]
            dv = dist[v] - dist[l]
            total = du + dv
            target = (total + 1) // 2  # ceil(total/2)

            if target <= du:
                ans.append(first_reach_up(u, target))
            else:
                remaining = target - du
                limit = dv - remaining
                ans.append(climb_with_limit(v, limit))

        return ans
# @lc code=end
