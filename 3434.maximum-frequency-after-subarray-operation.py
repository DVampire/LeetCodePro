#
# @lc app=leetcode id=3434 lang=python3
#
# [3434] Maximum Frequency After Subarray Operation
#

# @lc code=start
from typing import List

class Solution:
    def maxFrequency(self, nums: List[int], k: int) -> int:
        total_k = sum(1 for x in nums if x == k)
        best_gain = 0

        # Values are in [1..50]
        for v in range(1, 51):
            if v == k:
                continue

            cur = 0
            best = 0
            for a in nums:
                if a == v:
                    delta = 1
                elif a == k:
                    delta = -1
                else:
                    delta = 0

                # Kadane allowing empty subarray (so gain can't go below 0)
                cur = max(0, cur + delta)
                if cur > best:
                    best = cur

            if best > best_gain:
                best_gain = best

        return total_k + best_gain
# @lc code=end
