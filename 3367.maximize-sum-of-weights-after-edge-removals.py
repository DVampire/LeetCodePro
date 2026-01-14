#
# @lc app=leetcode id=3367 lang=python3
#
# [3367] Maximize Sum of Weights after Edge Removals
#

# @lc code=start
from collections import defaultdict

class Solution:
    def maximizeSumOfWeights(self, edges: List[List[int]], k: int) -> int:
        n = len(edges) + 1
        graph = defaultdict(list)
        for u, v, w in edges:
            graph[u].append((v, w))
            graph[v].append((u, w))
        
        dp = {}
        stack = [(0, -1, False)]
        
        while stack:
            node, parent, processed = stack.pop()
            
            if processed:
                gains = []
                base_sum = 0
                
                for neighbor, weight in graph[node]:
                    if neighbor == parent:
                        continue
                    base_sum += dp[neighbor][0]
                    gain = weight + dp[neighbor][1] - dp[neighbor][0]
                    if gain > 0:
                        gains.append(gain)
                
                gains.sort(reverse=True)
                
                dp0 = base_sum + sum(gains[:k])
                dp1 = base_sum + sum(gains[:k-1])
                
                dp[node] = (dp0, dp1)
            else:
                stack.append((node, parent, True))
                for neighbor, weight in graph[node]:
                    if neighbor != parent:
                        stack.append((neighbor, node, False))
        
        return dp[0][0]
# @lc code=end