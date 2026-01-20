#
# @lc app=leetcode id=3414 lang=python3
#
# [3414] Maximum Score of Non-overlapping Intervals
#

# @lc code=start
from bisect import bisect_right
from typing import List

class Solution:
    def maximumWeight(self, intervals: List[List[int]]) -> List[int]:
        # Add original index to intervals: [start, end, weight, original_index]
        # We use 0-based indexing for the intervals array internally.
        n = len(intervals)
        events = []
        for i in range(n):
            events.append(intervals[i] + [i])
        
        # Sort by end time. 
        # If end times are equal, sorting order doesn't strictly affect correctness of max weight,
        # but stable sort or specific secondary keys can make behavior deterministic.
        # We just sort by end time.
        events.sort(key=lambda x: x[1])
        
        # Precompute end times for binary search
        ends = [x[1] for x in events]
        
        # dp[k][i] stores the best (weight, negated_indices_tuple) 
        # choosing k intervals from the first i sorted intervals (events[0]...events[i-1]).
        # We use negated indices to leverage Python's default tuple comparison in max().
        # We want max weight, then min lexicographical indices.
        # Tuple comparison (w1, ids1) > (w2, ids2) checks w1 > w2, then ids1 > ids2.
        # If we store ids as (-i1, -i2, ...), then ids1 > ids2 corresponds to the lexicographically smaller set.
        
        # Initialize DP table
        # Rows 0 to 4 (representing 0 to 4 intervals chosen)
        # Cols 0 to n (representing prefix of sorted intervals)
        # Value: (weight, indices_tuple)
        # Initialize with a sentinel that is smaller than any valid outcome for k > 0.
        # For k=0, weight is 0, indices is ().
        
        dp = [[(-1, ())] * (n + 1) for _ in range(5)]
        for i in range(n + 1):
            dp[0][i] = (0, ())
            
        for i in range(1, n + 1):
            curr_interval = events[i-1]
            start, end, weight, original_idx = curr_interval
            
            # Find the index of the last interval that ends strictly before current start
            # bisect_right returns an insertion point p. 
            # All elements in ends[:p] are <= start - 1 < start.
            # So events[0...p-1] are compatible.
            # This corresponds to dp[...][p].
            p = bisect_right(ends, start - 1)
            
            for k in range(1, 5):
                # Option 1: Don't include current interval
                # Inherit from dp[k][i-1]
                best_score, best_indices = dp[k][i-1]
                
                # Option 2: Include current interval
                # We need to extend a valid solution of size k-1 from compatible intervals
                prev_score, prev_indices = dp[k-1][p]
                
                if prev_score != -1:
                    new_score = prev_score + weight
                    # Construct new indices tuple
                    # Convert negated indices back to positive to sort properly with new index
                    current_indices_list = sorted([-x for x in prev_indices] + [original_idx])
                    new_indices = tuple(-x for x in current_indices_list)
                    
                    # Compare
                    # Because we use negated indices, simple > comparison works for
                    # "MAX weight, then MIN lexicographical indices"
                    if (new_score, new_indices) > (best_score, best_indices):
                        best_score = new_score
                        best_indices = new_indices
                
                dp[k][i] = (best_score, best_indices)
        
        # The answer is the best among picking 1, 2, 3, or 4 intervals from all n intervals
        # i.e., max over k=1..4 of dp[k][n]
        final_res = (-1, ())
        for k in range(1, 5):
            if dp[k][n] > final_res:
                final_res = dp[k][n]
        
        # Convert negated indices back to original
        return sorted([-x for x in final_res[1]])

# @lc code=end