#
# @lc app=leetcode id=3630 lang=python3
#
# [3630] Partition Array for Maximum XOR and AND
#

# @lc code=start
from typing import List

class Solution:
    def maximizeXorAndXor(self, nums: List[int]) -> int:
        n = len(nums)
        BITS = 30
        ALL_BITS = (1 << BITS) - 1
        
        # Precompute XOR for each subset
        xor_all = [0] * (1 << n)
        for mask in range(1, 1 << n):
            lsb = mask & (-mask)
            idx = lsb.bit_length() - 1
            xor_all[mask] = xor_all[mask ^ lsb] ^ nums[idx]
        
        # Precompute AND for each subset (AND of empty set is 0)
        and_all = [0] * (1 << n)
        for mask in range(1, 1 << n):
            lsb = mask & (-mask)
            idx = lsb.bit_length() - 1
            if mask == lsb:
                and_all[mask] = nums[idx]
            else:
                and_all[mask] = and_all[mask ^ lsb] & nums[idx]
        
        # Precompute basis for each subset (for XOR linear space)
        basis_all = [[] for _ in range(1 << n)]
        for mask in range(1, 1 << n):
            lsb = mask & (-mask)
            idx = lsb.bit_length() - 1
            prev_basis = basis_all[mask ^ lsb][:]
            cur = nums[idx]
            for b in prev_basis:
                cur = min(cur, cur ^ b)
            if cur > 0:
                prev_basis.append(cur)
                prev_basis.sort(reverse=True)
            basis_all[mask] = prev_basis
        
        def max_xor_sum(s_mask):
            if s_mask == 0:
                return 0
            
            c = xor_all[s_mask]
            # We want to maximize x + (c XOR x) = c + 2*(x AND ~c)
            target = ALL_BITS ^ c  # bits where c is 0
            basis = basis_all[s_mask]
            
            # Greedy: find x in span that maximizes x AND target
            x = 0
            for b in basis:
                if (x ^ b) & target > x & target:
                    x ^= b
            
            return c + 2 * (x & target)
        
        max_value = 0
        full_mask = (1 << n) - 1
        
        for b_mask in range(1 << n):
            and_b = and_all[b_mask]
            s_mask = full_mask ^ b_mask
            xor_sum = max_xor_sum(s_mask)
            max_value = max(max_value, and_b + xor_sum)
        
        return max_value
# @lc code=end