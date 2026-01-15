#
# @lc app=leetcode id=3621 lang=python3
#
# [3621] Number of Integers With Popcount-Depth Equal to K I
#

# @lc code=start
class Solution:
    def popcountDepth(self, n: int, k: int) -> int:
        from functools import lru_cache
        
        def get_depth(x):
            if x == 1:
                return 0
            d = 1
            p = bin(x).count('1')
            while p != 1:
                d += 1
                p = bin(p).count('1')
            return d
        
        if k == 0:
            return 1 if n >= 1 else 0
        
        # Precompute depths for possible popcounts (up to ~60 for n <= 10^15)
        max_popcount = 60
        depth = [get_depth(i) for i in range(max_popcount + 1)]
        
        # Find valid popcounts p such that depth[p] == k - 1
        valid_popcounts = [p for p in range(1, max_popcount + 1) if depth[p] == k - 1]
        
        if not valid_popcounts:
            return 0
        
        # Digit DP to count numbers with a specific popcount
        bits = bin(n)[2:]
        num_bits = len(bits)
        
        @lru_cache(maxsize=None)
        def dp(pos, count, tight, target):
            if count > target:
                return 0
            if pos == num_bits:
                return 1 if count == target else 0
            
            limit = int(bits[pos]) if tight else 1
            result = 0
            for digit in range(limit + 1):
                result += dp(pos + 1, count + digit, tight and (digit == limit), target)
            return result
        
        result = sum(dp(0, 0, True, p) for p in valid_popcounts)
        
        # Exclude x = 1 if it was counted (x = 1 has popcount 1 but depth 0)
        if 1 in valid_popcounts and n >= 1:
            result -= 1
        
        return result
# @lc code=end