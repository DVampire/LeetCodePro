#
# @lc app=leetcode id=3462 lang=python3
#
# [3462] Maximum Sum With at Most K Elements
#

# @lc code=start
from typing import List

class Solution:
    def maxSum(self, grid: List[List[int]], limits: List[int], k: int) -> int:
        pool = []
        
        # Iterate through each row and its corresponding limit
        for row, limit in zip(grid, limits):
            if limit > 0:
                # Sort the row in descending order and collect the top 'limit' elements
                row_sorted = sorted(row, reverse=True)
                pool.extend(row_sorted[:limit])
        
        # Sort the entire pool of potential candidates globally
        pool.sort(reverse=True)
        
        # Sum the k largest elements from the pool to get the maximum sum
        # Since all elements are >= 0, picking k elements is optimal for "at most k"
        return sum(pool[:k])
# @lc code=end