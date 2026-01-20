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
        n = len(nums)
        if n == 0:
            return 0
        BITS = 20
        U = (1 << BITS) - 1
        MASK = 0
        for num in nums:
            MASK |= num
        bits = [b for b in range(BITS) if (MASK & (1 << b))]
        K = len(bits)
        f = [0] * (1 << BITS)
        for num in nums:
            f[num] += 1
        g = f[:]
        for bit in range(BITS):
            p = 1 << bit
            for mask in range(1 << BITS):
                if mask & p:
                    g[mask] += g[mask ^ p]
        ans = 0
        for s in range(1, 1 << K):
            mask_T = 0
            pop = 0
            for j in range(K):
                if s & (1 << j):
                    mask_T |= (1 << bits[j])
                    pop += 1
            zero_cnt = g[U ^ mask_T]
            req_size = n - zero_cnt
            num_subs = pow(2, n - req_size, MOD)
            if pop % 2 == 1:
                ans = (ans + num_subs) % MOD
            else:
                ans = (ans - num_subs + MOD) % MOD
        return ans
# @lc code=end