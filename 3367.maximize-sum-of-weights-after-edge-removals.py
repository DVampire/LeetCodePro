#
# @lc app=leetcode id=3367 lang=python3
#
# [3367] Maximize Sum of Weights after Edge Removals
#

# @lc code=start
from typing import List
import sys
sys.setrecursionlimit(10**6)

class Solution:
    def maximizeSumOfWeights(self, edges: List[List[int]], k: int) -> int:
        n = len(edges) + 1
        adj = [[] for _ in range(n)]
        for a, b, w in edges:
            adj[a].append((b, w))
            adj[b].append((a, w))
        
        def dfs(u: int, p: int) -> tuple[int, int]:
            base = 0
            deltas = []
            for v, w in adj[u]:
                if v == p:
                    continue
                no_v, with_v = dfs(v, u)
                base += no_v
                delta = w + with_v - no_v
                deltas.append(delta)
            deltas.sort(reverse=True)
            current = 0
            max_no = 0
            max_with = 0
            for i, d in enumerate(deltas):
                current += d
                r = i + 1
                if r <= k:
                    max_no = max(max_no, current)
                if k > 0 and r <= k - 1:
                    max_with = max(max_with, current)
            no_max = base + max_no
            with_max = base + max_with
            return no_max, with_max
        
        return dfs(0, -1)[0]

# @lc code=end