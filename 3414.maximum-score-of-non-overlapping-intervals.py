#
# @lc app=leetcode id=3414 lang=python3
#
# [3414] Maximum Score of Non-overlapping Intervals
#

# @lc code=start
import bisect

class Solution:
    def maximumWeight(self, intervals: List[List[int]]) -> List[int]:
        n = len(intervals)
        # Store intervals with their original index: [l, r, w, original_idx]
        indexed_intervals = []
        for i in range(n):
            indexed_intervals.append(intervals[i] + [i])
        
        # Sort by end time
        indexed_intervals.sort(key=lambda x: x[1])
        
        ends = [x[1] for x in indexed_intervals]

        # dp[k][i] = (max_weight, sorted_indices_list)
        # Use at most k intervals from first i intervals
        # k ranges from 1 to 4
        dp = [[(0, []) for _ in range(n + 1)] for _ in range(5)]

        for i in range(1, n + 1):
            l, r, w, idx = indexed_intervals[i-1]
            # Find the last interval that ends before current interval starts
            prev_idx = bisect.bisect_left(ends, l) 
            
            for k in range(1, 5):
                # Option 1: Don't include intervals[i-1]
                best_w, best_indices = dp[k][i-1]
                
                # Option 2: Include intervals[i-1]
                prev_w, prev_indices = dp[k-1][prev_idx]
                current_w = prev_w + w
                current_indices = sorted(prev_indices + [idx])
                
                if current_w > best_w:
                    best_w, best_indices = current_w, current_indices
                elif current_w == best_w and current_w > 0:
                    if not best_indices or current_indices < best_indices:
                        best_indices = current_indices
                
                dp[k][i] = (best_w, best_indices)

        # Find the best across all k for the full range n
        final_w, final_indices = 0, []
        for k in range(1, 5):
            w, indices = dp[k][n]
            if w > final_w:
                final_w, final_indices = w, indices
            elif w == final_w:
                if not final_indices or indices < final_indices:
                    final_indices = indices
        
        return final_indices
# @lc code=end