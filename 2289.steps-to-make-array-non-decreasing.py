#
# @lc app=leetcode id=2289 lang=python3
#
# [2289] Steps to Make Array Non-decreasing
#

from typing import List

# @lc code=start
class Solution:
    def totalSteps(self, nums: List[int]) -> int:
        n = len(nums)
        # dp[i] stores the number of steps after which nums[i] will be removed.
        # If never removed, dp[i] remains 0.
        dp = [0] * n
        # Stack stores indices of numbers that are potentially decreasing.
        # It helps find nearest greater element to the left.
        stack = []
        
        for i in range(n):
            # Current number of steps needed before removing current element.
            cur_steps = 0
            # Pop smaller or equal elements from the stack.
            # They cannot block current element from being removed by a larger left neighbor.
            # Keep track of maximum removal steps among popped elements.
            while stack and nums[stack[-1]] <= nums[i]:
                cur_steps = max(cur_steps, dp[stack[-1]])
                stack.pop()
            
            # If there is still a larger element on the left,
            # current element will be removed one step after all smaller/equal
            # elements between them are gone.
            if stack:
                dp[i] = cur_steps + 1
            else:
                # No larger element on the left => never removed.
                dp[i] = 0
            
            # Push current index onto stack.
            stack.append(i)
        
        # The answer is the maximum number of steps any element takes to be removed.
        return max(dp)
# @lc code=end