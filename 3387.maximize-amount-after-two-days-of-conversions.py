#
# @lc app=leetcode id=3387 lang=python3
#
# [3387] Maximize Amount After Two Days of Conversions
#

# @lc code=start
class Solution:
    def maxAmount(self, initialCurrency: str, pairs1: List[List[str]], rates1: List[float], pairs2: List[List[str]], rates2: List[float]) -> float:
        # Helper function to find maximum amounts for all currencies using Bellman-Ford algorithm
        def getMaxAmounts(pairs, rates, startCurrency):
            # Get all unique currencies
            currencies = set()
            for pair in pairs:
                currencies.add(pair[0])
                currencies.add(pair[1])
            
            # If startCurrency is not in the graph, add it
            currencies.add(startCurrency)
            currencies = list(currencies)
            
            # Initialize distances (amounts) - we want to maximize, so use negative infinity
            # But since we're dealing with multiplication, we'll use logarithms or just track max directly
            # Actually, let's track maximum amount directly
            amounts = {currency: 0.0 for currency in currencies}
            amounts[startCurrency] = 1.0
            
            # Relax edges up to len(currencies) - 1 times
            for _ in range(len(currencies)):
                updated = False
                # For each edge, try both directions
                for i, pair in enumerate(pairs):
                    src, dst = pair[0], pair[1]
                    rate = rates[i]
                    
                    # Forward conversion: src -> dst
                    if amounts[src] > 0 and amounts[src] * rate > amounts[dst]:
                        amounts[dst] = amounts[src] * rate
                        updated = True
                    
                    # Backward conversion: dst -> src (using inverse rate)
                    inverse_rate = 1.0 / rate
                    if amounts[dst] > 0 and amounts[dst] * inverse_rate > amounts[src]:
                        amounts[src] = amounts[dst] * inverse_rate
                        updated = True
                
                # If no update, we can stop early
                if not updated:
                    break
            
            return amounts
        
        # Day 1: Find maximum amounts for all currencies starting from initialCurrency
        day1Amounts = getMaxAmounts(pairs1, rates1, initialCurrency)
        
        # Day 2: For each currency we have amount from day 1, find maximum amount of initialCurrency
        maxResult = day1Amounts.get(initialCurrency, 0.0)
        
        # Get all currencies we can have after day 1
        for currency, amount in day1Amounts.items():
            if amount > 0:
                # Use this currency as starting point for day 2
                day2Amounts = getMaxAmounts(pairs2, rates2, currency)
                # Check how much initialCurrency we can get from this currency
                resultAmount = amount * day2Amounts.get(initialCurrency, 0.0)
                maxResult = max(maxResult, resultAmount)
        
        return maxResult
# @lc code=end