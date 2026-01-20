#
# @lc app=leetcode id=3367 lang=python3
#
# [3367] Maximize Sum of Weights after Edge Removals
#

# @lc code=start
import sys

# Increase recursion depth for deep trees
sys.setrecursionlimit(200000)

class Solution:
    def maximizeSumOfWeights(self, edges: List[List[int]], k: int) -> int:
        # Build adjacency list
        adj = [[] for _ in range(len(edges) + 1)]
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))
        
        # dp[u][0]: max weight in subtree u if edge to parent is NOT kept (u can take k children)
        # dp[u][1]: max weight in subtree u if edge to parent IS kept (u can take k-1 children)
        
        def dfs(u, p):
            # Base sum: assume we cut all edges to children
            base_sum = 0
            # List to store the gain (diff) if we keep an edge to a child
            diffs = []
            
            for v, w in adj[u]:
                if v == p:
                    continue
                
                res0, res1 = dfs(v, u)
                
                # If we cut edge (u, v), we get res0 from v's subtree
                base_sum += res0
                
                # Calculate the gain if we keep edge (u, v)
                # Gain = (weight + value if connected) - (value if not connected)
                gain = w + res1 - res0
                
                # We only consider keeping the edge if it improves the result
                if gain > 0:
                    diffs.append(gain)
            
            # Sort gains in descending order to pick the best ones
            diffs.sort(reverse=True)
            
            # Calculate dp[u][0]: can pick at most k children
            take_k = base_sum + sum(diffs[:k])
            
            # Calculate dp[u][1]: can pick at most k-1 children
            # If k is 0, we can't take any children if parent edge is kept (though k >= 1 per constraints)
            take_k_minus_1 = base_sum + sum(diffs[:max(0, k - 1)])
            
            return take_k, take_k_minus_1

        return dfs(0, -1)[0]

# @lc code=end