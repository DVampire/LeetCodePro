#
# @lc app=leetcode id=3757 lang=python3
#
# [3757] Number of Effective Subsequences
#

# @lc code=start
from typing import List
from collections import Counter

class Solution:
    def countEffective(self, nums: List[int]) -> int:
        MOD = 10**9 + 7
        
        # Compute the overall OR
        U = 0
        for v in nums:
            U |= v
        
        if U == 0:
            return 0
        
        # g[m] = count of elements with (v & U) = m
        g = Counter(v & U for v in nums)
        
        # Generate all submasks of U
        submasks = []
        M = U
        while True:
            submasks.append(M)
            if M == 0:
                break
            M = (M - 1) & U
        
        # SOS DP: sos[m] = sum of g[m'] for m' subset of m
        sos = {m: g.get(m, 0) for m in submasks}
        
        bit = 1
        while bit <= U:
            if bit & U:
                for m in submasks:
                    if m & bit:
                        sos[m] += sos[m ^ bit]
            bit <<= 1
        
        # Compute the answer using inclusion-exclusion
        # For non-empty submask M of U: contribution = (-1)^(popcount(M)+1) * 2^sos[U^M]
        ans = 0
        for M in submasks:
            if M == 0:
                continue
            pop = bin(M).count('1')
            complement = U ^ M
            cnt = sos[complement]
            contribution = pow(2, cnt, MOD)
            if pop % 2 == 1:
                ans = (ans + contribution) % MOD
            else:
                ans = (ans - contribution) % MOD
        
        return ans % MOD
# @lc code=end