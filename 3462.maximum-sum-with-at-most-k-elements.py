#
# @lc app=leetcode id=3462 lang=python3
#
# [3462] Maximum Sum With at Most K Elements
#
# @lc code=start
class Solution:
    def maxSum(self, grid: List[List[int]], limits: List[int], k: int) -> int:
        candidates = []
        
        # For each row, collect the top limits[i] elements
        for i in range(len(grid)):
            row_sorted = sorted(grid[i], reverse=True)
            # Take at most limits[i] elements from this row
            candidates.extend(row_sorted[:limits[i]])
        
        # Sort all candidates in descending order
        candidates.sort(reverse=True)
        
        # Take the top k elements
        return sum(candidates[:k])
# @lc code=end