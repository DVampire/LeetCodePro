#
# @lc app=leetcode id=3753 lang=python3
#
# [3753] Total Waviness of Numbers in Range II
#

# @lc code=start
from functools import lru_cache

class Solution:
    def totalWaviness(self, num1: int, num2: int) -> int:
        def count_up_to(n):
            if n < 0:
                return 0
            s = str(n)
            L = len(s)
            
            @lru_cache(maxsize=None)
            def dp(pos, tight, prev, prev_cmp, started):
                # Returns (count, total_waviness)
                if pos == L:
                    return (1, 0)
                
                limit = int(s[pos]) if tight else 9
                cnt, wav = 0, 0
                
                for d in range(limit + 1):
                    new_tight = tight and (d == limit)
                    
                    if not started:
                        if d == 0:
                            c, w = dp(pos + 1, new_tight, -1, -2, False)
                        else:
                            c, w = dp(pos + 1, new_tight, d, -2, True)
                        cnt += c
                        wav += w
                    else:
                        peak_valley = 0
                        # Check if prev is a peak or valley
                        if prev_cmp == -1 and d < prev:  # prev2 < prev1 and d < prev1 => peak
                            peak_valley = 1
                        elif prev_cmp == 1 and d > prev:  # prev2 > prev1 and d > prev1 => valley
                            peak_valley = 1
                        
                        # Calculate new prev_cmp
                        if prev < d:
                            new_cmp = -1
                        elif prev > d:
                            new_cmp = 1
                        else:
                            new_cmp = 0
                        
                        c, w = dp(pos + 1, new_tight, d, new_cmp, True)
                        cnt += c
                        wav += w + peak_valley * c
                
                return (cnt, wav)
            
            return dp(0, True, -1, -2, False)[1]
        
        return count_up_to(num2) - count_up_to(num1 - 1)
# @lc code=end