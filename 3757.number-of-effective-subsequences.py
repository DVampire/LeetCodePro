#
# @lc app=leetcode id=3757 lang=python3
#
# [3757] Number of Effective Subsequences
#

# @lc code=start
from typing import List

class Solution:
    def countEffective(self, nums: List[int]) -> int:
        MOD = 10**9 + 7
        T = 0
        for x in nums:
            T |= x
        
        if T == 0:
            return 0
            
        # Map the set bits of T to a continuous range [0, m-1]
        bits = [i for i in range(21) if (T >> i) & 1]
        m = len(bits)
        mapping = {bit: i for i, bit in enumerate(bits)}
        
        # Count frequencies of mapped numbers
        cnt = [0] * (1 << m)
        for x in nums:
            nx = 0
            for i in range(m):
                if (x >> bits[i]) & 1:
                    nx |= (1 << i)
            cnt[nx] += 1
            
        # SOS DP (Zeta Transform) to calculate f(mask)
        # f(mask) = number of elements whose mapped value is a subset of mask
        for i in range(m):
            bit = 1 << i
            for mask in range(1 << m):
                if mask & bit:
                    cnt[mask] += cnt[mask ^ bit]
        
        # Precompute powers of 2
        pow2 = [1] * (len(nums) + 1)
        for i in range(1, len(nums) + 1):
            pow2[i] = (pow2[i-1] * 2) % MOD
            
        # Number of subsets B such that OR(B) = T
        # Using PIE: Count(OR(B) = T) = sum_{mask subseteq T} (-1)^(m - popcount(mask)) * 2^f(mask)
        subset_count_T = 0
        for mask in range(1 << m):
            popcount = bin(mask).count('1')
            term = pow2[cnt[mask]]
            if (m - popcount) % 2 == 1:
                subset_count_T = (subset_count_T - term) % MOD
            else:
                subset_count_T = (subset_count_T + term) % MOD
        
        # Total subsets is 2^n. Effective are those where OR(B) < T.
        # ans = 2^n - subset_count_T
        total_subsets = pow2[len(nums)]
        ans = (total_subsets - subset_count_T) % MOD
        
        return ans
# @lc code=end