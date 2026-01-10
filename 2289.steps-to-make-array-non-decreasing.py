#
# @lc app=leetcode id=2289 lang=python3
#
# [2289] Steps to Make Array Non-decreasing
#

# @lc code=start
class Solution:
    def totalSteps(self, nums: List[int]) -> int:
        # ans will store the maximum number of steps required
        ans = 0
        # stack will store pairs of (value, step_at_which_it_is_removed)
        stack = []
        
        for x in nums:
            # t represents the time (step) when the current element x is removed
            t = 0
            # Pop elements from the stack that are smaller than or equal to x.
            # x can only be removed after all these elements are removed.
            while stack and x >= stack[-1][0]:
                t = max(t, stack.pop()[1])
            
            # If the stack is empty, it means no element to the left is greater than x.
            # Therefore, x will never be removed.
            if not stack:
                t = 0
            else:
                # If the stack is not empty, the top of the stack is the nearest element
                # to the left that is strictly greater than x. x will be removed
                # one step after the maximum removal time of the elements between them.
                t = t + 1
            
            # Update the global maximum steps
            ans = max(ans, t)
            # Push the current element and its removal time onto the stack
            stack.append((x, t))
            
        return ans
# @lc code=end