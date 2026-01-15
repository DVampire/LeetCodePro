#
# @lc app=leetcode id=3367 lang=python3
#
# [3367] Maximize Sum of Weights after Edge Removals
#

from typing import List

# @lc code=start
class Solution:
    def maximizeSumOfWeights(self, edges: List[List[int]], k: int) -> int:
        import sys
        sys.setrecursionlimit(300000)
        
        n = len(edges) + 1
        graph = [[] for _ in range(n)]
        for u,v,w in edges:
            graph[u].append((v,w))
            graph[v].append((u,w))
        
        def dfs(u:int , parent:int):
            total_f_children = 0
            gains = []
            
            # Process each child
            for v,w in graph[u]:
                if v == parent:
                    continue
                f_v,g_v = dfs(v,u)
                total_f_children += f_v
                # Gain if we keep the edge (u,v)
                gain = w + g_v - f_v
                gains.append(gain)
            
            # Sort gains descending
            gains.sort(reverse=True)
            
            # Compute f[u]: maximum when u has no parent edge (can keep up to k child edges)
            sum_f = total_f_children
            cnt = 0
            for gain in gains:
                if gain <= 0 or cnt >= k:
                    break
                sum_f += gain
                cnt += 1
            
            # Compute g[u]: maximum when u has a parent edge kept (can keep up to k-1 child edges)
            sum_g = total_f_children
            cnt = 0
            for gain in gains:
                if gain <= 0 or cnt >= k-1:
                    break
                sum_g += gain
                cnt += 1
            
            return sum_f ,sum_g
        
        res,_ = dfs(0,-1)
        return res
# @lc code=end