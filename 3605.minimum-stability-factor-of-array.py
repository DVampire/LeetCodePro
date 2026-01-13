#
# @lc app=leetcode id=3605 lang=python3
#
# [3605] Minimum Stability Factor of Array
#

# @lc code=start
from typing import List
import math

class Solution:
    def minStable(self, nums: List[int], maxC: int) -> int:
        n = len(nums)

        # Precompute floor(log2(i))
        logs = [0] * (n + 1)
        for i in range(2, n + 1):
            logs[i] = logs[i // 2] + 1

        # Build GCD sparse table, storing only needed lengths per level
        st = [nums[:]]
        k = 1
        while (1 << k) <= n:
            half = 1 << (k - 1)
            size = n - (1 << k) + 1
            prev = st[k - 1]
            cur = [0] * size
            for i in range(size):
                cur[i] = math.gcd(prev[i], prev[i + half])
            st.append(cur)
            k += 1

        def range_gcd(l: int, r: int) -> int:
            length = r - l + 1
            kk = logs[length]
            return math.gcd(st[kk][l], st[kk][r - (1 << kk) + 1])

        def feasible(x: int) -> bool:
            L = x + 1
            if L > n:
                return True
            used = 0
            last_pick = -1
            # windows start i = 0..n-L
            end_offset = L - 1
            for i in range(0, n - L + 1):
                if range_gcd(i, i + end_offset) >= 2:
                    # not stabbed yet
                    if last_pick < i:
                        used += 1
                        last_pick = i + end_offset  # greedy pick right endpoint
                        if used > maxC:
                            return False
            return True

        lo, hi = 0, n
        while lo < hi:
            mid = (lo + hi) // 2
            if feasible(mid):
                hi = mid
            else:
                lo = mid + 1
        return lo
# @lc code=end
