#
# @lc app=leetcode id=3373 lang=python3
#
# [3373] Maximize the Number of Target Nodes After Connecting Trees II
#

# @lc code=start
import collections
from typing import List

class Solution:
    def maxTargetNodes(self, edges1: List[List[int]], edges2: List[List[int]]) -> List[int]:
        def get_tree_info(n, edges):
            adj = [[] for _ in range(n)]
            for u, v in edges:
                adj[u].append(v)
                adj[v].append(u)
            
            colors = [-1] * n
            colors[0] = 0
            queue = collections.deque([0])
            while queue:
                u = queue.popleft()
                for v in adj[u]:
                    if colors[v] == -1:
                        colors[v] = 1 - colors[u]
                        queue.append(v)
            
            count0 = sum(1 for c in colors if c == 0)
            count1 = n - count0
            return colors, count0, count1

        n = len(edges1) + 1
        m = len(edges2) + 1
        
        colors1, k0, k1 = get_tree_info(n, edges1)
        _, c0, c1 = get_tree_info(m, edges2)
        
        # Max contribution from T2 is the maximum of the two bipartite color counts
        max_from_t2 = max(c0, c1)
        
        ans = [0] * n
        for i in range(n):
            # Nodes in T1 with same color as i are at even distance
            if colors1[i] == 0:
                ans[i] = k0 + max_from_t2
            else:
                ans[i] = k1 + max_from_t2
                
        return ans
# @lc code=end