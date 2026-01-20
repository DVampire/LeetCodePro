#
# @lc app=leetcode id=3488 lang=python3
#
# [3488] Closest Equal Element Queries
#

# @lc code=start
from collections import defaultdict
from bisect import bisect_left

class Solution:
    def solveQueries(self, nums: List[int], queries: List[int]) -> List[int]:
        n = len(nums)
        positions = defaultdict(list)
        
        # Group indices by value
        for i, num in enumerate(nums):
            positions[num].append(i)
            
        results = []
        
        for q_idx in queries:
            val = nums[q_idx]
            indices = positions[val]
            k = len(indices)
            
            if k <= 1:
                results.append(-1)
                continue
            
            # Find the position of the current query index in the sorted list of indices
            # Since we know q_idx is in indices, bisect_left will find it efficiently.
            pos_in_list = bisect_left(indices, q_idx)
            
            # Identify left and right neighbors in the circular sense
            # The list 'indices' is sorted.
            # Left neighbor index in 'indices' list:
            left_neighbor_idx = indices[(pos_in_list - 1 + k) % k]
            # Right neighbor index in 'indices' list:
            right_neighbor_idx = indices[(pos_in_list + 1) % k]
            
            # Calculate circular distance function
            def dist(i, j):
                d = abs(i - j)
                return min(d, n - d)
            
            d1 = dist(q_idx, left_neighbor_idx)
            d2 = dist(q_idx, right_neighbor_idx)
            
            results.append(min(d1, d2))
            
        return results
# @lc code=end