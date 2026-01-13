#
# @lc app=leetcode id=3413 lang=python3
#
# [3413] Maximum Coins From K Consecutive Bags
#

# @lc code=start
class Solution:
    def maximumCoins(self, coins: List[List[int]], k: int) -> int:
        coins.sort()
        
        max_coins = 0
        starts = set()
        
        # Collect critical starting positions
        for l, r, c in coins:
            starts.add(l)  # Window starts at segment boundary
            starts.add(max(1, r - k + 1))  # Window ends at segment boundary
        
        # For each starting position, calculate total coins
        for start in starts:
            end = start + k - 1
            total = 0
            
            # Calculate coins by checking overlap with each segment
            for l, r, c in coins:
                overlap_start = max(start, l)
                overlap_end = min(end, r)
                if overlap_start <= overlap_end:
                    total += (overlap_end - overlap_start + 1) * c
            
            max_coins = max(max_coins, total)
        
        return max_coins
# @lc code=end