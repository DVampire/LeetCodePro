#
# @lc app=leetcode id=3729 lang=python3
#
# [3729] Count Distinct Subarrays Divisible by K in Sorted Array
#

# @lc code=start
from typing import List

class Solution:
    def numGoodSubarrays(self, nums: List[int], k: int) -> int:
        if k == 0:
            return 0
        n = len(nums)
        groups = []
        i = 0
        while i < n:
            v = nums[i]
            cnt = 0
            while i < n and nums[i] == v:
                cnt += 1
                i += 1
            groups.append((v, cnt))
        ans = 0
        mod_dict = {}
        shift = 0
        for v, c in groups:
            bv = v % k
            for r in range(1, c + 1):
                gamma = (bv * r) % k
                needed = (k - gamma) % k
                rel = (needed - shift) % k
                ans += mod_dict.get(rel, 0)
                if gamma == 0:
                    ans += 1
            delta = (bv * c) % k
            shift = (shift + delta) % k
            rel_new = (delta - shift) % k
            if rel_new in mod_dict:
                mod_dict[rel_new] += 1
            else:
                mod_dict[rel_new] = 1
        return ans

# @lc code=end