#
# @lc app=leetcode id=3462 lang=python3
#
# [3462] Maximum Sum With at Most K Elements
#

# @lc code=start
from typing import List

class Solution:
    def maxSum(self, grid: List[List[int]], limits: List[int], k: int) -> int:
        n = len(grid)
        all_elements = []
        for i in range(n):
            for j in range(len(grid[i])):
                all_elements.append((grid[i][j], i))
        all_elements.sort(key=lambda x: -x[0])
        picked = [0] * n
        total = 0
        cnt = 0
        for val, row in all_elements:
            if picked[row] < limits[row] and cnt < k:
                total += val
                picked[row] += 1
                cnt += 1
        return total

# @lc code=end