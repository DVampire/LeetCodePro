#
# @lc app=leetcode id=3457 lang=python3
#
# [3457] Eat Pizzas!
#
# @lc code=start
class Solution:
    def maxWeight(self, pizzas: List[int]) -> int:
        pizzas.sort(reverse=True)
        n = len(pizzas)
        total_days = n // 4
        odd_days = (total_days + 1) // 2
        even_days = total_days // 2
        
        total_weight = 0
        
        # Gain the top odd_days pizzas (Z on odd days)
        for i in range(odd_days):
            total_weight += pizzas[i]
        
        # Gain every other pizza in the next 2*even_days pizzas (Y on even days)
        for i in range(even_days):
            total_weight += pizzas[odd_days + 2 * i + 1]
        
        return total_weight
# @lc code=end