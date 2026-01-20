#
# @lc app=leetcode id=3509 lang=python3
#
# [3509] Maximum Product of Subsequences With an Alternating Sum Equal to K
#

# @lc code=start
from typing import List

class Solution:
    def maxProduct(self, nums: List[int], k: int, limit: int) -> int:
        offset = 1800
        SZ = 3601
        dp1 = [[[0 for _ in range(2)] for _ in range(2)] for _ in range(SZ)]
        dp2 = [[[0 for _ in range(2)] for _ in range(2)] for _ in range(SZ)]

        # Non-zero product DP
        non_zero = [x for x in nums if x > 0]
        prev = dp1
        prev[offset][0][0] = 1
        for v in non_zero:
            curr = dp2 if prev is dp1 else dp1
            # reset curr
            for d in range(SZ):
                for p in range(2):
                    for st in range(2):
                        curr[d][p][st] = 0
            for d in range(SZ):
                for p in range(2):
                    for st in range(2):
                        prod = prev[d][p][st]
                        if prod == 0:
                            continue
                        # skip
                        curr[d][p][st] = max(curr[d][p][st], prod)
                        # take
                        sign = 1 if p == 0 else -1
                        new_real = (d - offset) + sign * v
                        new_d = int(new_real + offset)
                        if 0 <= new_d < SZ:
                            new_p = 1 - p
                            new_st = 1
                            new_prod = prod * v
                            if new_prod <= limit:
                                curr[new_d][new_p][new_st] = max(curr[new_d][new_p][new_st], new_prod)
            prev = curr

        target = offset + k
        max_prod = 0
        if 0 <= target < SZ:
            max_prod = max(prev[target][0][1], prev[target][1][1])
        if max_prod > 0:
            return max_prod

        # Product 0 DP: check existence with at least one 0
        # Reset dps
        for dp_arr in [dp1, dp2]:
            for d in range(SZ):
                for p in range(2):
                    for s in range(2):
                        dp_arr[d][p][s] = 0
        prev = dp1
        prev[offset][0][0] = 1
        for v in nums:
            curr = dp2 if prev is dp1 else dp1
            # reset curr
            for d in range(SZ):
                for p in range(2):
                    for hz in range(2):
                        curr[d][p][hz] = 0
            for d in range(SZ):
                for p in range(2):
                    for hz in range(2):
                        if prev[d][p][hz] == 0:
                            continue
                        # skip
                        curr[d][p][hz] = 1
                        # take
                        sign = 1 if p == 0 else -1
                        new_real = (d - offset) + sign * v
                        new_d = int(new_real + offset)
                        if 0 <= new_d < SZ:
                            new_p = 1 - p
                            new_hz = 1 if v == 0 else hz
                            curr[new_d][new_p][new_hz] = 1
            prev = curr

        has_zero_k = False
        if 0 <= target < SZ:
            if prev[target][0][1] == 1 or prev[target][1][1] == 1:
                has_zero_k = True
        if has_zero_k:
            return 0
        return -1

# @lc code=end