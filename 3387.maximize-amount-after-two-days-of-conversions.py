#
# @lc app=leetcode id=3387 lang=python3
#
# [3387] Maximize Amount After Two Days of Conversions
#

# @lc code=start
import heapq
from collections import defaultdict
from typing import List

class Solution:
    def maxAmount(self, initialCurrency: str, pairs1: List[List[str]], rates1: List[float], pairs2: List[List[str]], rates2: List[float]) -> float:
        # Build graph for day 1 (bidirectional)
        graph1 = defaultdict(list)
        for i, (src, dst) in enumerate(pairs1):
            rate = rates1[i]
            graph1[src].append((dst, rate))
            graph1[dst].append((src, 1.0 / rate))
        
        # Build graph for day 2 (bidirectional)
        graph2 = defaultdict(list)
        for i, (src, dst) in enumerate(pairs2):
            rate = rates2[i]
            graph2[src].append((dst, rate))
            graph2[dst].append((src, 1.0 / rate))
        
        # Find maximum amount of each currency after day 1 starting from initialCurrency
        max_after_day1 = self.findMaxConversions(graph1, initialCurrency)
        
        # For each currency we might have after day 1, find max initialCurrency on day 2
        result = 1.0  # If we don't convert at all
        
        for currency, amount_day1 in max_after_day1.items():
            # Find max initialCurrency we can get from this currency on day 2
            max_from_currency = self.findMaxConversions(graph2, currency)
            if initialCurrency in max_from_currency:
                result = max(result, amount_day1 * max_from_currency[initialCurrency])
        
        return result
    
    def findMaxConversions(self, graph, start):
        # Use Dijkstra-like algorithm with max heap to find maximum conversion rates
        max_amount = {start: 1.0}
        # Max heap: use negative values for Python's min heap
        heap = [(-1.0, start)]
        
        while heap:
            neg_amount, curr = heapq.heappop(heap)
            amount = -neg_amount
            
            # Skip if we've already found a better path to this currency
            if amount < max_amount.get(curr, 0):
                continue
            
            # Try all conversions from current currency
            for next_curr, rate in graph[curr]:
                new_amount = amount * rate
                if new_amount > max_amount.get(next_curr, 0):
                    max_amount[next_curr] = new_amount
                    heapq.heappush(heap, (-new_amount, next_curr))
        
        return max_amount
# @lc code=end