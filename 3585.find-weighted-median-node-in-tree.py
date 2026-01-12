#
# @lc app=leetcode id=3585 lang=python3
#
# [3585] Find Weighted Median Node in Tree
#

# @lc code=start
import sys

# Increase recursion depth for deep trees
sys.setrecursionlimit(200000)

class Solution:
    def findMedian(self, n: int, edges: list[list[int]], queries: list[list[int]]) -> list[int]:
        adj = [[] for _ in range(n)]
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))
            
        MAX_LOG = n.bit_length()
        up = [[-1] * MAX_LOG for _ in range(n)]
        tin = [0] * n
        tout = [0] * n
        depth_w = [0] * n
        timer = 0
        
        def dfs(u, p, dw):
            nonlocal timer
            timer += 1
            tin[u] = timer
            depth_w[u] = dw
            up[u][0] = p
            for i in range(1, MAX_LOG):
                if up[u][i-1] != -1:
                    up[u][i] = up[up[u][i-1]][i-1]
                else:
                    break
            
            for v, w in adj[u]:
                if v != p:
                    dfs(v, u, dw + w)
            tout[u] = timer

        dfs(0, -1, 0)

        def is_ancestor(u, v):
            return tin[u] <= tin[v] and tout[u] >= tout[v]

        def get_lca(u, v):
            if is_ancestor(u, v): return u
            if is_ancestor(v, u): return v
            for i in range(MAX_LOG - 1, -1, -1):
                if up[u][i] != -1 and not is_ancestor(up[u][i], v):
                    u = up[u][i]
            return up[u][0]

        ans = []
        for u, v in queries:
            if u == v:
                ans.append(u)
                continue
            
            lca = get_lca(u, v)
            dist_u_lca = depth_w[u] - depth_w[lca]
            dist_v_lca = depth_w[v] - depth_w[lca]
            total_w = dist_u_lca + dist_v_lca
            
            # Target: dist(u, x) >= total_w / 2  => 2 * dist(u, x) >= total_w
            if 2 * dist_u_lca >= total_w:
                # Median is on path u -> lca. It's an ancestor of u.
                # Find the lowest ancestor x such that 2 * (depth_w[u] - depth_w[x]) >= total_w
                curr = u
                for i in range(MAX_LOG - 1, -1, -1):
                    anc = up[curr][i]
                    if anc != -1 and is_ancestor(lca, anc):
                        if 2 * (depth_w[u] - depth_w[anc]) < total_w:
                            curr = anc
                ans.append(up[curr][0])
            else:
                # Median is on path lca -> v. It's an ancestor of v.
                # Find the highest ancestor x such that 2 * dist(u, x) >= total_w
                # dist(u, x) = dist(u, lca) + dist(lca, x) = (depth_w[u]-depth_w[lca]) + (depth_w[x]-depth_w[lca])
                # 2 * (depth_w[u] + depth_w[x] - 2 * depth_w[lca]) >= total_w
                curr = v
                for i in range(MAX_LOG - 1, -1, -1):
                    anc = up[curr][i]
                    if anc != -1 and is_ancestor(lca, anc):
                        if 2 * (depth_w[u] + depth_w[anc] - 2 * depth_w[lca]) >= total_w:
                            curr = anc
                ans.append(curr)
                
        return ans
# @lc code=end