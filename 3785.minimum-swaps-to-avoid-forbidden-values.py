#
# @lc app=leetcode id=3785 lang=python3
#
# [3785] Minimum Swaps to Avoid Forbidden Values
#

# @lc code=start
from typing import List
from collections import Counter

class Solution:
    def minSwaps(self, nums: List[int], forbidden: List[int]) -> int:
        n = len(nums)

        # Count occurrences in nums and forbidden
        occ = Counter(nums)
        fcnt = Counter(forbidden)

        # Feasibility check: for every value v, occ[v] <= n - fcnt[v]
        for v, c in occ.items():
            if c + fcnt.get(v, 0) > n:
                return -1

        # Count bad indices (nums[i] == forbidden[i]) per value
        badCnt = Counter()
        k = 0
        for a, b in zip(nums, forbidden):
            if a == b:
                badCnt[a] += 1
                k += 1

        if k == 0:
            return 0

        mx = max(badCnt.values())
        return max((k + 1) // 2, mx)
# @lc code=end
