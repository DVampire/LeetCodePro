#
# @lc app=leetcode id=2289 lang=python3
#
# [2289] Steps to Make Array Non-decreasing
#

from typing import List

# @lc code=start
class Solution:
    def totalSteps(self, nums: List[int]) -> int:
        # stack holds (value, steps_to_be_removed)
        stack = []
        ans = 0

        for x in nums:
            cur = 0
            # Pop all elements <= x; they cannot be the "killer" of x.
            # While popping, collect the max removal time among them.
            while stack and x >= stack[-1][0]:
                cur = max(cur, stack[-1][1])
                stack.pop()

            if not stack:
                cur = 0
            else:
                cur += 1

            ans = max(ans, cur)
            stack.append((x, cur))

        return ans
# @lc code=end
