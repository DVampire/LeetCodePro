#
# @lc app=leetcode id=3695 lang=python3
#
# [3695] Maximize Alternating Sum Using Swaps
#

from typing import List
from collections import defaultdict

# @lc code=start
class DSU:
    def __init__(self, n: int):
        self.parent = list(range(n))
        self.size = [1] * n

    def find(self, x: int) -> int:
        while self.parent[x] != x:
            self.parent[x] = self.parent[self.parent[x]]
            x = self.parent[x]
        return x

    def union(self, a: int, b: int) -> None:
        ra, rb = self.find(a), self.find(b)
        if ra == rb:
            return
        if self.size[ra] < self.size[rb]:
            ra, rb = rb, ra
        self.parent[rb] = ra
        self.size[ra] += self.size[rb]


class Solution:
    def maxAlternatingSum(self, nums: List[int], swaps: List[List[int]]) -> int:
        n = len(nums)
        dsu = DSU(n)

        for p, q in swaps:
            dsu.union(p, q)

        # root -> [values_list, even_count, odd_count]
        comp_vals = defaultdict(list)
        even_cnt = defaultdict(int)
        odd_cnt = defaultdict(int)

        for i, v in enumerate(nums):
            r = dsu.find(i)
            comp_vals[r].append(v)
            if i % 2 == 0:
                even_cnt[r] += 1
            else:
                odd_cnt[r] += 1

        ans = 0
        for r, vals in comp_vals.items():
            e = even_cnt[r]
            o = odd_cnt[r]
            vals.sort()  # ascending
            k = len(vals)

            # prefix sums for O(1) range sums
            pref = [0] * (k + 1)
            for i, x in enumerate(vals):
                pref[i + 1] = pref[i] + x

            sum_small_odd = pref[o]                  # sum of smallest o values
            sum_large_even = pref[k] - pref[k - e]   # sum of largest e values

            ans += sum_large_even - sum_small_odd

        return ans
# @lc code=end
