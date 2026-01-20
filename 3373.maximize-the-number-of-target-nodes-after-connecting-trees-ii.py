#
# @lc app=leetcode id=3373 lang=python3
#
# [3373] Maximize the Number of Target Nodes After Connecting Trees II
#

# @lc code=start
from typing import List
import collections

class Solution:
    def maxTargetNodes(self, edges1: List[List[int]], edges2: List[List[int]]) -> List[int]:
        def build_adj(edges, N):
            adj = [[] for _ in range(N)]
            for a, b in edges:
                adj[a].append(b)
                adj[b].append(a)
            return adj
        
        def bfs_color(adj, N, root):
            color = [-1] * N
            color[root] = 0
            q = collections.deque([root])
            sz = [0, 0]
            sz[0] = 1
            while q:
                u = q.popleft()
                for v in adj[u]:
                    if color[v] == -1:
                        color[v] = 1 - color[u]
                        sz[color[v]] += 1
                        q.append(v)
            return color, sz
        
        n = len(edges1) + 1
        adj1 = build_adj(edges1, n)
        color1, sz1 = bfs_color(adj1, n, 0)
        
        m = len(edges2) + 1
        adj2 = build_adj(edges2, m)
        _, sz2 = bfs_color(adj2, m, 0)
        
        GLOBAL = max(sz2[0], sz2[1])
        
        answer = [0] * n
        for i in range(n):
            answer[i] = sz1[color1[i]] + GLOBAL
        
        return answer
# @lc code=end