#
# @lc app=leetcode id=3686 lang=python3
#
# [3686] Number of Stable Subsequences
#

# @lc code=start
from typing import List

class Solution:
    def countStableSubsequences(self, nums: List[int]) -> int:
        MOD = 10**9 + 7

        # dp0_1, dp0_2: ending with even, run length 1 or 2
        # dp1_1, dp1_2: ending with odd,  run length 1 or 2
        dp0_1 = dp0_2 = dp1_1 = dp1_2 = 0

        for x in nums:
            b = x & 1
            if b == 0:
                old0_1, old0_2, old1_1, old1_2 = dp0_1, dp0_2, dp1_1, dp1_2

                add_to_0_1 = (1 + old1_1 + old1_2) % MOD          # start or switch from odd
                add_to_0_2 = old0_1 % MOD                         # extend even run 1 -> 2

                dp0_1 = (dp0_1 + add_to_0_1) % MOD
                dp0_2 = (dp0_2 + add_to_0_2) % MOD
            else:
                old0_1, old0_2, old1_1, old1_2 = dp0_1, dp0_2, dp1_1, dp1_2

                add_to_1_1 = (1 + old0_1 + old0_2) % MOD          # start or switch from even
                add_to_1_2 = old1_1 % MOD                         # extend odd run 1 -> 2

                dp1_1 = (dp1_1 + add_to_1_1) % MOD
                dp1_2 = (dp1_2 + add_to_1_2) % MOD

        return (dp0_1 + dp0_2 + dp1_1 + dp1_2) % MOD
# @lc code=end
