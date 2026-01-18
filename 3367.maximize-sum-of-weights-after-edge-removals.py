#
# @lc app=leetcode id=3367 lang=python3
#
# [3367] Maximize Sum of Weights after Edge Removals
#

# @lc code=start
from typing import List

class Solution:
    def maximizeSumOfWeights(self, edges: List[List[int]], k: int) -> int:
        n = len(edges) + 1
        adj = [[] for _ in range(n)]
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))
        
        # Iterative post-order traversal to avoid recursion depth issues
        parent = [-1] * n
        order = []
        stack = [0]
        parent[0] = 0
        
        while stack:
            u = stack.pop()
            order.append(u)
            for v, w in adj[u]:
                if parent[v] == -1 and v != 0:
                    parent[v] = u
                    stack.append(v)
        
        dp0 = [0] * n
        dp1 = [0] * n
        
        # Process nodes in reverse topological order (bottom-up)
        for u in reversed(order):
            base_sum = 0
            gains = []
            
            for v, w in adj[u]:
                if v == parent[u]:
                    continue
                
                # Base contribution: max sum if edge (u, v) is removed
                base_sum += dp0[v]
                
                # Potential gain if edge (u, v) is kept
                gain = w + dp1[v] - dp0[v]
                if gain > 0:
                    gains.append(gain)
            
            # Sort gains in descending order to pick the best ones
            gains.sort(reverse=True)
            
            # Sum of top gains for dp0 (up to k edges to children)
            top_k_sum = sum(gains[:k])
            dp0[u] = base_sum + top_k_sum
            
            # Sum of top gains for dp1 (up to k-1 edges to children)
            top_k_minus_1_sum = sum(gains[:k-1])
            dp1[u] = base_sum + top_k_minus_1_sum
            
        return dp0[0]

# @lc code=end