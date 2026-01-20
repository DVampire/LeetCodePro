#
# @lc app=leetcode id=3413 lang=python3
#
# [3413] Maximum Coins From K Consecutive Bags
#

# @lc code=start
class Solution:
    def maximumCoins(self, coins: List[List[int]], k: int) -> int:
        def solve(intervals):
            intervals.sort() # Sort by start time
            n = len(intervals)
            max_coins = 0
            current_sum = 0
            r = 0
            
            # We iterate l from 0 to n-1. The window starts at intervals[l][0].
            # The window range is [start_pos, end_pos]
            for l in range(n):
                start_pos = intervals[l][0]
                end_pos = start_pos + k - 1
                
                # Expand r to include all intervals that start within the window
                # The condition intervals[r][0] <= end_pos ensures the interval starts before the window ends.
                # It might extend beyond the window end, which we handle later.
                while r < n and intervals[r][0] <= end_pos:
                    count = (intervals[r][1] - intervals[r][0] + 1) * intervals[r][2]
                    current_sum += count
                    r += 1
                
                # Now intervals[l...r-1] are the ones that start within or before the window [start_pos, end_pos].
                # Specifically, intervals[l] starts exactly at start_pos.
                # The last added interval, intervals[r-1], might go beyond end_pos.
                
                # Calculate overshoot for the last interval added (r-1)
                overshoot = 0
                if r > 0:
                    last_interval = intervals[r-1]
                    if last_interval[1] > end_pos:
                        overshoot = (last_interval[1] - end_pos) * last_interval[2]
                
                max_coins = max(max_coins, current_sum - overshoot)
                
                # Before moving l to l+1, remove the contribution of interval l from current_sum
                # because the next window will start at intervals[l+1][0], which is > intervals[l][1] (non-overlapping)
                # or at least > intervals[l][0].
                # Actually, strictly speaking, we are removing interval l because it falls out of the 'start' side
                # as we consider the specific structure of moving from one interval start to the next.
                current_sum -= (intervals[l][1] - intervals[l][0] + 1) * intervals[l][2]
                
            return max_coins

        # Case 1: Window starts at the beginning of an interval
        ans1 = solve(coins)
        
        # Case 2: Window ends at the end of an interval.
        # This is equivalent to solving the problem on a reversed number line
        # where segments [l, r] become [-r, -l].
        # Example: [1, 3] becomes [-3, -1]. Window size k remains same.
        # We sort these new segments and run the same logic.
        coins2 = [[-c[1], -c[0], c[2]] for c in coins]
        ans2 = solve(coins2)
        
        return max(ans1, ans2)

# @lc code=end