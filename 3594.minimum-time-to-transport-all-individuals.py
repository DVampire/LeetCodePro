#
# @lc app=leetcode id=3594 lang=python3
#
# [3594] Minimum Time to Transport All Individuals
#

from typing import List

# @lc code=start
class Solution:
    def minTime(self, n: int, k: int, m: int, time: List[int], mul: List[float]) -> float:
        INF = float('inf')
        ALL = 1 << n
        pop = [bin(i).count('1') for i in range(ALL)]
        valid_groups = []
        group_max = []
        for sub in range(1, ALL):
            if pop[sub] > k:
                continue
            mt = 0
            temp = sub
            while temp:
                i = temp.bit_length() - 1
                mt = max(mt, time[i])
                temp ^= (1 << i)
            valid_groups.append(sub)
            group_max.append(mt)
        memo = {}
        def dp(mask: int, boat: int, stage: int) -> float:
            if mask == 0:
                return 0.0
            key = (mask, boat, stage)
            if key in memo:
                return memo[key]
            ans = INF
            if boat == 1:  # at start, forward trip
                for j in range(len(valid_groups)):
                    sub = valid_groups[j]
                    if (sub & mask) == sub:
                        maxt = group_max[j]
                        d = maxt * mul[stage]
                        adv = int(d) % m
                        ns = (stage + adv) % m
                        nm = mask ^ sub
                        ans = min(ans, d + dp(nm, 0, ns))
            else:  # at dest, return trip
                for i in range(n):
                    if (mask & (1 << i)) == 0:
                        rt = time[i] * mul[stage]
                        adv = int(rt) % m
                        ns = (stage + adv) % m
                        nm = mask | (1 << i)
                        ans = min(ans, rt + dp(nm, 1, ns))
            memo[key] = ans
            return ans
        res = dp(ALL - 1, 1, 0)
        return -1.0 if res == INF else res

# @lc code=end
