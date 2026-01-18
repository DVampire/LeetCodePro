#
# @lc app=leetcode id=3387 lang=python3
#
# [3387] Maximize Amount After Two Days of Conversions
#

# @lc code=start
import collections
from typing import List

class Solution:
    def maxAmount(self, initialCurrency: str, pairs1: List[List[str]], rates1: List[float], pairs2: List[List[str]], rates2: List[float]) -> float:
        def get_rates(start_node: str, pairs: List[List[str]], rates: List[float]) -> dict:
            # Build an adjacency list for the currency conversion graph
            adj = collections.defaultdict(list)
            for i in range(len(pairs)):
                u, v = pairs[i]
                r = rates[i]
                adj[u].append((v, r))
                adj[v].append((u, 1.0 / r))
            
            # Use BFS to find the unique rate from start_node to all reachable currencies
            rates_map = {start_node: 1.0}
            queue = collections.deque([start_node])
            while queue:
                u = queue.popleft()
                for v, r in adj[u]:
                    if v not in rates_map:
                        rates_map[v] = rates_map[u] * r
                        queue.append(v)
            return rates_map
        
        # Find the maximum amount of each currency we can have after Day 1
        day1_amounts = get_rates(initialCurrency, pairs1, rates1)
        
        # Find the conversion rates from initialCurrency to other currencies on Day 2
        day2_rates = get_rates(initialCurrency, pairs2, rates2)
        
        # Calculate the maximum final initialCurrency amount
        max_val = 1.0
        for curr, amt in day1_amounts.items():
            # If we can convert this currency back to initialCurrency on Day 2
            if curr in day2_rates:
                # amt is units of curr. 1 initialCurrency = day2_rates[curr] units of curr.
                # So 1 unit of curr = 1 / day2_rates[curr] initialCurrency.
                final_amt = amt / day2_rates[curr]
                if final_amt > max_val:
                    max_val = final_amt
                    
        return max_val
# @lc code=end