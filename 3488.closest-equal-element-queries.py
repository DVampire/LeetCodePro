#
# @lc app=leetcode id=3488 lang=python3
#
# [3488] Closest Equal Element Queries
#

# @lc code=start
class Solution:
    def solveQueries(self, nums: List[int], queries: List[int]) -> List[int]:
        from collections import defaultdict
        
        n = len(nums)
        
        # Group indices by their values
        value_indices = defaultdict(list)
        for i, num in enumerate(nums):
            value_indices[num].append(i)
        
        # Precompute minimum distance for each index
        min_dist = [-1] * n
        
        for indices in value_indices.values():
            k = len(indices)
            if k == 1:
                continue  # No other index with same value
            
            for p in range(k):
                idx = indices[p]
                # Neighbors in the circular list of indices
                prev_idx = indices[(p - 1) % k]
                next_idx = indices[(p + 1) % k]
                
                # Calculate circular distances in the original array
                dist_prev = min(abs(idx - prev_idx), n - abs(idx - prev_idx))
                dist_next = min(abs(idx - next_idx), n - abs(idx - next_idx))
                
                min_dist[idx] = min(dist_prev, dist_next)
        
        return [min_dist[q] for q in queries]
# @lc code=end