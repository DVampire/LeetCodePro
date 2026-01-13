#
# @lc app=leetcode id=3768 lang=python3
#
# [3768] Minimum Inversion Count in Subarrays of Fixed Length
#

# @lc code=start
from typing import List
import bisect

class Fenwick:
    def __init__(self, n: int):
        self.n = n
        self.bit = [0] * (n + 1)

    def add(self, i: int, delta: int) -> None:
        while i <= self.n:
            self.bit[i] += delta
            i += i & -i

    def sum(self, i: int) -> int:
        s = 0
        while i > 0:
            s += self.bit[i]
            i -= i & -i
        return s

class Solution:
    def minInversionCount(self, nums: List[int], k: int) -> int:
        n = len(nums)
        if k <= 1:
            return 0

        # Coordinate compression
        vals = sorted(set(nums))
        def rk(x: int) -> int:
            return bisect.bisect_left(vals, x) + 1  # 1-indexed

        m = len(vals)
        bit = Fenwick(m)

        # Inversion count for first window
        inv = 0
        count_in = 0
        for i in range(k):
            r = rk(nums[i])
            leq = bit.sum(r)
            inv += count_in - leq  # previous > current
            bit.add(r, 1)
            count_in += 1

        ans = inv

        # Slide windows
        for start in range(0, n - k):
            ans = min(ans, inv)

            x = nums[start]
            y = nums[start + k]
            rx = rk(x)
            ry = rk(y)

            # Remove leftmost x
            bit.add(rx, -1)
            removed = bit.sum(rx - 1)  # count of elements < x in remaining window
            inv -= removed

            # Add rightmost y
            # current window size is k-1 before insertion
            greater = (k - 1) - bit.sum(ry)  # count of elements > y
            inv += greater
            bit.add(ry, 1)

        ans = min(ans, inv)
        return ans
# @lc code=end
