#
# @lc app=leetcode id=3725 lang=python3
#
# [3725] Count Ways to Choose Coprime Integers from Rows
#

# @lc code=start
class Solution:
    def countCoprime(self, mat: List[List[int]]) -> int:
        from math import gcd
        from collections import Counter
        
        MOD = 10**9 + 7
        
        # dp[g] = number of ways to choose integers from processed rows with GCD = g
        dp = Counter(mat[0])
        
        # Process remaining rows
        for row in mat[1:]:
            new_dp = Counter()
            row_count = Counter(row)
            for prev_gcd, count in dp.items():
                for val, freq in row_count.items():
                    new_gcd = gcd(prev_gcd, val)
                    new_dp[new_gcd] = (new_dp[new_gcd] + count * freq) % MOD
            dp = new_dp
        
        return dp.get(1, 0)
# @lc code=end