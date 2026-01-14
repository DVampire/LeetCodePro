#
# @lc app=leetcode id=3387 lang=python3
#
# [3387] Maximize Amount After Two Days of Conversions
#

# @lc code=start
from collections import defaultdict, deque

class Solution:
    def maxAmount(self, initialCurrency: str, pairs1: List[List[str]], rates1: List[float], pairs2: List[List[str]], rates2: List[float]) -> float:
        
        def get_rates(pairs, rates, start):
            graph = defaultdict(list)
            for i, (a, b) in enumerate(pairs):
                graph[a].append((b, rates[i]))
                graph[b].append((a, 1.0 / rates[i]))
            
            result = {start: 1.0}
            queue = deque([start])
            while queue:
                curr = queue.popleft()
                for neighbor, rate in graph[curr]:
                    if neighbor not in result:
                        result[neighbor] = result[curr] * rate
                        queue.append(neighbor)
            
            return result
        
        day1_rates = get_rates(pairs1, rates1, initialCurrency)
        day2_rates = get_rates(pairs2, rates2, initialCurrency)
        
        max_amount = 1.0
        for currency in day1_rates:
            if currency in day2_rates:
                amount = day1_rates[currency] / day2_rates[currency]
                max_amount = max(max_amount, amount)
        
        return max_amount
# @lc code=end