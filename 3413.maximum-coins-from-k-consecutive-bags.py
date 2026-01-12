#
# @lc app=leetcode id=3413 lang=python3
#
# [3413] Maximum Coins From K Consecutive Bags
#

# @lc code=start
class Solution:
    def maximumCoins(self, coins: List[List[int]], k: int) -> int:
        coins.sort()
        n = len(coins)
        
        def solve(intervals):
            res = 0
            current_sum = 0
            j = 0
            for i in range(n):
                # Window starts at intervals[i][0], ends at intervals[i][0] + k - 1
                window_end = intervals[i][0] + k - 1
                while j < n and intervals[j][1] <= window_end:
                    current_sum += (intervals[j][1] - intervals[j][0] + 1) * intervals[j][2]
                    j += 1
                
                # Partial segment at the end
                extra = 0
                if j < n and intervals[j][0] <= window_end:
                    extra = (window_end - intervals[j][0] + 1) * intervals[j][2]
                
                res = max(res, current_sum + extra)
                
                # Remove the current starting segment from sum before moving i
                current_sum -= (intervals[i][1] - intervals[i][0] + 1) * intervals[i][2]
            return res

        # Case 1: Window starts at the beginning of a segment
        ans1 = solve(coins)
        
        # Case 2: Window ends at the end of a segment
        # We can flip the segments and reuse the same logic
        flipped_coins = []
        for l, r, c in coins:
            flipped_coins.append([-r, -l, c])
        flipped_coins.sort()
        ans2 = solve(flipped_coins)
        
        return max(ans1, ans2)
# @lc code=end