#
# @lc app=leetcode id=3753 lang=python3
#
# [3753] Total Waviness of Numbers in Range II
#

# @lc code=start
from functools import lru_cache

class Solution:
    def totalWaviness(self, num1: int, num2: int) -> int:
        MOD = 10**9 + 7
        
        def count(n):
            if n <= 0:
                return 0
            s = str(n)
            m = len(s)
            
            @lru_cache(maxsize=None)
            def dp(pos, tight, pp, p):
                # pp = prev_prev digit (-1 if not set)
                # p = prev digit (-1 if number hasn't started)
                if pos == m:
                    return (1, 0)
                
                limit = int(s[pos]) if tight else 9
                cnt, wav = 0, 0
                
                for d in range(limit + 1):
                    nt = tight and (d == limit)
                    
                    if p == -1 and d == 0:
                        # Still in leading zeros
                        c, w = dp(pos + 1, nt, -1, -1)
                    elif p == -1:
                        # First significant digit
                        c, w = dp(pos + 1, nt, -1, d)
                    else:
                        # Check if prev (p) is peak or valley
                        add = 0
                        if pp != -1:
                            if pp < p > d:  # peak
                                add = 1
                            elif pp > p < d:  # valley
                                add = 1
                        c, w = dp(pos + 1, nt, p, d)
                        w = (w + c * add) % MOD
                    
                    cnt = (cnt + c) % MOD
                    wav = (wav + w) % MOD
                
                return (cnt, wav)
            
            return dp(0, True, -1, -1)[1]
        
        return (count(num2) - count(num1 - 1) + MOD) % MOD
# @lc code=end