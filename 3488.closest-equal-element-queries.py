#
# @lc app=leetcode id=3488 lang=python3
#
# [3488] Closest Equal Element Queries
#

# @lc code=start
from typing import List

class Solution:
    def solveQueries(self, nums: List[int], queries: List[int]) -> List[int]:
        n = len(nums)
        # Step 1: Group indices for each unique value
        pos = {}
        for i, v in enumerate(nums):
            if v not in pos:
                pos[v] = []
            pos[v].append(i)
        
        # Step 2: Precompute minimum circular distance for every index
        min_distances = [-1] * n
        for v in pos:
            indices = pos[v]
            k = len(indices)
            if k > 1:
                for i in range(k):
                    curr = indices[i]
                    # Distance to the previous index in the sorted list (counter-clockwise path)
                    # Python's indices[i-1] handles the wrap-around to the last element when i=0
                    d_prev = (curr - indices[i - 1] + n) % n
                    # Distance to the next index in the sorted list (clockwise path)
                    d_next = (indices[(i + 1) % k] - curr + n) % n
                    
                    min_distances[curr] = min(d_prev, d_next)
        
        # Step 3: Answer each query using the precomputed distances
        return [min_distances[q] for q in queries]
# @lc code=end