#
# @lc app=leetcode id=3462 lang=python3
#
# [3462] Maximum Sum With at Most K Elements
#

# @lc code=start
class Solution:
    def maxSum(self, grid: List[List[int]], limits: List[int], k: int) -> int:
        candidates = []
        
        for i, row in enumerate(grid):
            # Sort row in descending order and take top limits[i] elements
            sorted_row = sorted(row, reverse=True)
            candidates.extend(sorted_row[:limits[i]])
        
        # Sort all candidates in descending order
        candidates.sort(reverse=True)
        
        # Take top k elements and return their sum
        return sum(candidates[:k])
# @lc code=end