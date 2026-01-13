#
# @lc app=leetcode id=3488 lang=python3
#
# [3488] Closest Equal Element Queries
#
# @lc code=start
class Solution:
    def solveQueries(self, nums: List[int], queries: List[int]) -> List[int]:
        from collections import defaultdict
        
        # Group indices by value
        value_to_indices = defaultdict(list)
        for i, num in enumerate(nums):
            value_to_indices[num].append(i)
        
        n = len(nums)
        result = []
        
        for query_idx in queries:
            value = nums[query_idx]
            indices = value_to_indices[value]
            
            # If only one index has this value
            if len(indices) == 1:
                result.append(-1)
                continue
            
            # Find minimum distance to other indices with same value
            min_dist = float('inf')
            for idx in indices:
                if idx != query_idx:
                    # Calculate circular distance
                    linear_dist = abs(query_idx - idx)
                    circular_dist = min(linear_dist, n - linear_dist)
                    min_dist = min(min_dist, circular_dist)
            
            result.append(min_dist)
        
        return result
# @lc code=end