#
# @lc app=leetcode id=3630 lang=python3
#
# [3630] Partition Array for Maximum XOR and AND
#

from typing import List

# @lc code=start
class Solution:
    def maximizeXorAndXor(self, nums: List[int]) -> int:
        n = len(nums)
        m = 1 << n
        full = m - 1

        # Precompute XOR for all masks
        xorMask = [0] * m
        for mask in range(1, m):
            lb = mask & -mask
            i = (lb.bit_length() - 1)
            xorMask[mask] = xorMask[mask ^ lb] ^ nums[i]

        # Precompute AND for all masks; empty mask -> 0
        andMask = [0] * m
        for mask in range(1, m):
            lb = mask & -mask
            i = (lb.bit_length() - 1)
            prev = mask ^ lb
            if prev == 0:
                andMask[mask] = nums[i]
            else:
                andMask[mask] = andMask[prev] & nums[i]

        # Compute bestXorPairSum for all masks: max_{s submask} xor[s] + (xor[mask]^xor[s])
        bestX = [0] * m
        for mask in range(m):
            T = xorMask[mask]
            best = 0
            s = mask
            while True:
                x = xorMask[s]
                cand = x + (T ^ x)
                if cand > best:
                    best = cand
                if s == 0:
                    break
                s = (s - 1) & mask
            bestX[mask] = best

        ans = 0
        for b in range(m):
            r = full ^ b
            cand = andMask[b] + bestX[r]
            if cand > ans:
                ans = cand
        return ans
# @lc code=end
