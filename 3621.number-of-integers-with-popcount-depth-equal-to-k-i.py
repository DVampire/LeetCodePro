#
# @lc app=leetcode id=3621 lang=python3
#
# [3621] Number of Integers With Popcount-Depth Equal to K I
#

import math

# @lc code=start
class Solution:
    def popcountDepth(self, n: int, k: int) -> int:
        if k == 0:
            return 1
        
        # Precompute depths for popcount values 1 to 60
        depths = {1: 0}
        def get_depth(c):
            if c in depths: return depths[c]
            depths[c] = 1 + get_depth(bin(c).count('1'))
            return depths[c]

        # Find all c in [1, 60] such that depth(c) == k - 1
        target_popcounts = []
        for c in range(1, 61):
            if get_depth(c) == k - 1:
                target_popcounts.append(c)
        
        if not target_popcounts:
            return 0

        def count_with_popcount(n, target):
            if target < 0: return 0
            res = 0
            current_popcount = 0
            s = bin(n)[2:]
            L = len(s)
            for i in range(L):
                if s[i] == '1':
                    # If we place a '0' at this bit, we need to choose 'target - current_popcount'
                    # '1's from the remaining 'L - 1 - i' bits.
                    remaining_bits = L - 1 - i
                    needed_bits = target - current_popcount
                    if 0 <= needed_bits <= remaining_bits:
                        res += math.comb(remaining_bits, needed_bits)
                    current_popcount += 1
            if current_popcount == target:
                res += 1
            return res

        ans = 0
        for c in target_popcounts:
            ans += count_with_popcount(n, c)
        
        # If k=1, the logic counts x=1 (popcount 1), but depth(1)=0, not 1.
        if k == 1:
            ans -= 1
            
        return ans
# @lc code=end