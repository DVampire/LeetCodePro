#
# @lc app=leetcode id=3387 lang=python3
#
# [3387] Maximize Amount After Two Days of Conversions
#

# @lc code=start
from collections import defaultdict, deque
from typing import List

class Solution:
    def maxAmount(self, initialCurrency: str, pairs1: List[List[str]], rates1: List[float], pairs2: List[List[str]], rates2: List[float]) -> float:
        
        def get_reachable_rates(pairs: List[List[str]], rates: List[float], start_node: str):
            adj = defaultdict(list)
            for (u, v), r in zip(pairs, rates):
                adj[u].append((v, r))
                adj[v].append((u, 1.0 / r))
            
            rates_map = {}
            rates_map[start_node] = 1.0
            queue = deque([start_node])
            
            while queue:
                curr = queue.popleft()
                curr_rate = rates_map[curr]
                
                for neighbor, rate in adj[curr]:
                    if neighbor not in rates_map:
                        rates_map[neighbor] = curr_rate * rate
                        queue.append(neighbor)
            return rates_map

        # Calculate rates on Day 1 starting from initialCurrency
        # rates_day1[C] will be the amount of currency C we get for 1 unit of initialCurrency
        rates_day1 = get_reachable_rates(pairs1, rates1, initialCurrency)
        
        # Calculate rates on Day 2 starting from initialCurrency
        # rates_day2[C] will be the amount of currency C we get for 1 unit of initialCurrency
        # Consequently, 1 unit of C converts back to (1 / rates_day2[C]) units of initialCurrency
        rates_day2 = get_reachable_rates(pairs2, rates2, initialCurrency)
        
        max_val = 0.0
        
        # Iterate over all currencies reachable on Day 1
        for currency, amount_day1 in rates_day1.items():
            # Check if this currency can be converted back to initialCurrency on Day 2
            # This implies it must be reachable from initialCurrency in the Day 2 graph
            if currency in rates_day2:
                rate_day2 = rates_day2[currency]
                # Calculate the final amount after converting back
                # amount_day1 is (initial -> currency)
                # rate_day2 is (initial -> currency) on day 2
                # The reverse conversion (currency -> initial) is 1 / rate_day2
                final_amount = amount_day1 / rate_day2
                if final_amount > max_val:
                    max_val = final_amount
                    
        return max_val
# @lc code=end