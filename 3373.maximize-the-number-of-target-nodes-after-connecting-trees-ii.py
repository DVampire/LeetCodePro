#
# @lc app=leetcode id=3373 lang=python3
#
# [3373] Maximize the Number of Target Nodes After Connecting Trees II
#

# @lc code=start
from typing import List

class Solution:
    def maxTargetNodes(self, edges1: List[List[int]], edges2: List[List[int]]) -> List[int]:
        def color_and_sizes(n: int, edges: List[List[int]]):
            adj = [[] for _ in range(n)]
            for u, v in edges:
                adj[u].append(v)
                adj[v].append(u)

            color = [-1] * n
            stack = [0]
            color[0] = 0
            while stack:
                u = stack.pop()
                for v in adj[u]:
                    if color[v] == -1:
                        color[v] = color[u] ^ 1
                        stack.append(v)

            cnt0 = sum(1 for c in color if c == 0)
            cnt1 = n - cnt0
            return color, (cnt0, cnt1)

        n = len(edges1) + 1
        m = len(edges2) + 1

        c1, (a0, a1) = color_and_sizes(n, edges1)
        _, (b0, b1) = color_and_sizes(m, edges2)

        best_tree2 = max(b0, b1)
        sizes1 = (a0, a1)

        ans = [0] * n
        for i in range(n):
            ans[i] = sizes1[c1[i]] + best_tree2
        return ans
# @lc code=end
