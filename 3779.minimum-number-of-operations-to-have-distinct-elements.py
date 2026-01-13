#
# @lc app=leetcode id=3779 lang=python3
#
# [3779] Minimum Number of Operations to Have Distinct Elements
#

from typing import List

# @lc code=start
class Solution:
    def minOperations(self, nums: List[int]) -> int:
        n = len(nums)

        # p = smallest index such that nums[p:] is all distinct
        p = n

        # Values are in [1, 1e5]
        seen = [0] * 100001

        for i in range(n - 1, -1, -1):
            v = nums[i]
            if seen[v]:
                # First duplicate encountered from the right => boundary found
                break
            seen[v] = 1
            p = i

        return (p + 2) // 3
# @lc code=end
