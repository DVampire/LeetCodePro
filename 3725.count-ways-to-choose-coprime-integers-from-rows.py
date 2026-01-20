#
# @lc app=leetcode id=3725 lang=python3
#
# [3725] Count Ways to Choose Coprime Integers from Rows
#

# @lc code=start
from math import gcd
from collections import Counter
from typing import List

class Solution:
    def countCoprime(self, mat: List[List[int]]) -> int:
        MOD = 10**9 + 7
        
        # Initialize dp with the first row
        # dp[g] stores the number of ways to have a running GCD of g
        dp = [0] * 151
        
        row_counts = Counter(mat[0])
        for val, count in row_counts.items():
            dp[val] = (dp[val] + count) % MOD
            
        # Process subsequent rows
        for i in range(1, len(mat)):
            new_dp = [0] * 151
            row_counts = Counter(mat[i])
            
            # We only need to iterate through existing GCDs in dp
            # Since values are small (<=150), we can just iterate 1..150
            # Optimization: collect current valid gcds to avoid iterating 150 times if sparse
            current_gcds = [g for g in range(1, 151) if dp[g] > 0]
            
            if not current_gcds:
                return 0
                
            for g in current_gcds:
                ways = dp[g]
                for val, count in row_counts.items():
                    new_g = gcd(g, val)
                    new_dp[new_g] = (new_dp[new_g] + ways * count) % MOD
            
            dp = new_dp
            
        return dp[1]

# @lc code=end