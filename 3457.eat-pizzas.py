#
# @lc app=leetcode id=3457 lang=python3
#
# [3457] Eat Pizzas!
#

# @lc code=start
from typing import List

class Solution:
    def maxWeight(self, pizzas: List[int]) -> int:
        pizzas.sort(reverse=True)
        n = len(pizzas)
        k = n // 4
        num_odd = (k + 1) // 2
        num_even = k // 2
        total = sum(pizzas[:num_odd])
        pos = num_odd
        for i in range(num_even):
            total += pizzas[pos + 2 * i + 1]
        return total

# @lc code=end