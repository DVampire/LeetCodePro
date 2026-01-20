#
# @lc app=leetcode id=3785 lang=python3
#
# [3785] Minimum Swaps to Avoid Forbidden Values
#

from typing import List
import collections

# @lc code=start
class Solution:
    def minSwaps(self, nums: List[int], forbidden: List[int]) -> int:
        n = len(nums)
        count_nums = collections.Counter(nums)
        count_forb = collections.Counter(forbidden)
        for v, cnt in count_nums.items():
            if cnt > n - count_forb[v]:
                return -1
        bad_count = collections.Counter()
        k = 0
        for i in range(n):
            if nums[i] == forbidden[i]:
                v = nums[i]
                bad_count[v] += 1
                k += 1
        if k == 0:
            return 0
        max_bad = max(bad_count.values())
        m = k // 2 if max_bad <= k // 2 else k - max_bad
        return k - m

# @lc code=end