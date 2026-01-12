#
# @lc app=leetcode id=2289 lang=python3
#
# [2289] Steps to Make Array Non-decreasing
#

# @lc code=start
class Solution:
    def totalSteps(self, nums: List[int]) -> int:
        n = len(nums)
        # dp[i] will store the step at which nums[i] is removed.
        # If dp[i] is 0, nums[i] is never removed.
        dp = [0] * n
        stack = [] # Monotonic stack to store indices of elements
        
        for i in range(n):
            current_max_dp = 0
            # Pop elements that are smaller than or equal to the current element.
            # These elements would be removed before or at the same time as 
            # the current element if they were to the right of a larger element.
            while stack and nums[stack[-1]] <= nums[i]:
                current_max_dp = max(current_max_dp, dp[stack.pop()])
            
            # If the stack is not empty, the top element is the nearest element
            # to the left that is strictly greater than nums[i].
            if stack:
                # nums[i] will be removed 1 step after all elements between 
                # it and nums[stack[-1]] are removed.
                dp[i] = current_max_dp + 1
            else:
                # No element to the left is greater than nums[i].
                dp[i] = 0
            
            stack.append(i)
            
        return max(dp)
# @lc code=end