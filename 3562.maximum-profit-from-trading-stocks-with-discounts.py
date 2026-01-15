#
# @lc app=leetcode id=3562 lang=python3
#
# [3562] Maximum Profit from Trading Stocks with Discounts
#

# @lc code=start
from typing import List
import math

class Solution:
    def maxProfit(self,
                  n: int,
                  present: List[int],
                  future: List[int],
                  hierarchy: List[List[int]],
                  budget: int) -> int:
        # Build adjacency list
        adj = [[] for _ in range(n+1)]
        for par, ch in hierarchy:
            adj[par].append(ch)
        
        # Precompute half prices
        half_present = [math.floor(p/2) for p in present]
        # Shift indices to 1-based
        present = [0] + present          # index i corresponds to employee i
        future = [0] + future
        half_present = [0] + half_present
        
        # Memoization dictionary
        memo = {}
        
        def dfs(u):
            """Return two lists:
               res[0]: list length budget+1 for state where parent NOT bought
               res[1]: list length budget+1 for state where parent BOUGHT"""
            # Initialize knapsack arrays for combining children
            # cur0 : combined results from children assuming current node NOT bought
            # cur1 : combined results from children assuming current node BOUGHT
            cur0 = [-10**9] * (budget+1)
            cur0[0] = 0
            cur1 = [-10**9] * (budget+1)
            cur1[0] = 0
            
            # Process children
            for v in adj[u]:
                # Recursively compute DP for child
                child_res = dfs(v)
                # For cur0 : current node NOT bought -> children see parent NOT bought
                # Merge cur0 with child_res[0]
                new_cur0 = [-10**9] * (budget+1)
                for i in range(budget+1):
                    if cur0[i] == -10**9:
                        continue
                    for j in range(budget+1-i):
                        if child_res[0][j] == -10**9:
                            continue
                        new_cur0[i+j] = max(new_cur0[i+j], cur0[i] + child_res[0][j])
                cur0 = new_cur0
                
                # For cur1 : current node BOUGHT -> children see parent BOUGHT
                # Merge cur1 with child_res[1]
                new_cur1 = [-10**9] * (budget+1)
                for i in range(budget+1):
                    if cur1[i] == -10**9:
                        continue
                    for j in range(budget+1-i):
                        if child_res[1][j] == -10**9:
                            continue
                        new_cur1[i+j] = max(new_cur1[i+j], cur1[i] + child_res[1][j])
                cur1 = new_cur1
            
            # Now compute results for both states of parent
            res_parent_not_bought = [-10**9] * (budget+1)
            res_parent_bought    = [-10**9] * (budget+1)
            
            # Common options:
            # Option A : do NOT buy current node -> simply use cur0
            # Option B : buy current node -> add self profit after shifting by appropriate cost
            
            # For res_parent_not_bought:
            full_cost = present[u]
            full_profit = future[u] - full_cost
            # Option A
            for c in range(budget+1):
                res_parent_not_bought[c] = max(res_parent_not_bought[c], cur0[c])
            # Option B
            for c in range(full_cost, budget+1):
                prev_profit = cur1[c-full_cost]
                if prev_profit != -10**9:
                    candidate = prev_profit + full_profit
                    res_parent_not_bought[c] = max(res_parent_not_bought[c], candidate)
                    
            # For res_parent_bought:
            disc_cost = half_present[u]
            disc_profit = future[u] - disc_cost
            # Option A again uses cur0
            for c in range(budget+1):
                res_parent_bought[c] = max(res_parent_bought[c], cur0[c])
            # Option B uses discounted self-cost
            for c in range(disc_cost, budget+1):
                prev_profit = cur1[c-disc_cost]
                if prev_profit != -10**9:
                    candidate = prev_profit + disc_profit
                    res_parent_bought[c] = max(res_parent_bought[c], candidate)
                    
            return res_parent_not_bought , res_parent_bought
        
        root_res = dfs(1)[0]   # root has no boss -> treat as parent NOT bought
        return max(root_res)
# @lc code=end