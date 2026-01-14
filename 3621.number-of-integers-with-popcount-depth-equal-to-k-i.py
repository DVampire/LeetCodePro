#
# @lc app=leetcode id=3621 lang=python3
#
# [3621] Number of Integers With Popcount-Depth Equal to K I
#
# @lc code=start
class Solution:
    def popcountDepth(self, n: int, k: int) -> int:
        from functools import lru_cache
        
        # Precompute depths for popcount values 1 to 64
        depth = [0] * 65
        depth[1] = 0
        for i in range(2, 65):
            popcount_i = bin(i).count('1')
            depth[i] = 1 + depth[popcount_i]
        
        # Special case: k = 0
        if k == 0:
            return 1 if n >= 1 else 0
        
        # Find target popcounts with depth k-1
        target_popcounts = [c for c in range(1, 65) if depth[c] == k - 1]
        
        # Count numbers <= n with specific popcount using digit DP
        def count_with_popcount(num, target_pc):
            if num == 0:
                return 0
            
            binary = bin(num)[2:]
            length = len(binary)
            
            @lru_cache(maxsize=None)
            def dp(pos, count, tight, started):
                if count > target_pc:
                    return 0
                if pos == length:
                    return 1 if count == target_pc and started else 0
                
                limit = int(binary[pos]) if tight else 1
                result = 0
                
                for digit in range(0, limit + 1):
                    if not started and digit == 0:
                        result += dp(pos + 1, count, False, False)
                    else:
                        new_count = count + digit
                        new_tight = tight and (digit == limit)
                        result += dp(pos + 1, new_count, new_tight, True)
                
                return result
            
            ans = dp(0, 0, True, False)
            if target_pc == 1 and ans > 0:
                ans -= 1  # Exclude x = 1 which has depth 0
            return ans
        
        # Sum counts for all target popcounts
        total = 0
        for pc in target_popcounts:
            total += count_with_popcount(n, pc)
        
        return total
# @lc code=end