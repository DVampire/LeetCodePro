#
# @lc app=leetcode id=2289 lang=python3
#
# [2289] Steps to Make Array Non-decreasing
#

# @lc code=start
from typing import List

class Solution:
    def totalSteps(self, nums: List[int]) -> int:
        # The stack will store pairs of (value, steps_to_remove)
        stack = []
        max_steps = 0
        
        for x in nums:
            current_steps = 0
            # While the current element is greater than or equal to the top of the stack,
            # it means the current element will 'wait' for the top element to be removed.
            # The time it takes for the current element to be reachable by a larger element
            # to the left is at least the time taken to remove the elements in between.
            while stack and stack[-1][0] <= x:
                # We take the maximum of steps needed to remove the intermediate smaller elements.
                current_steps = max(current_steps, stack.pop()[1])
            
            if stack:
                # If the stack is not empty, it means there is a larger element to the left.
                # The current element will be removed 1 step after all intermediate elements
                # (that were smaller than it) are gone.
                current_steps += 1
            else:
                # If the stack is empty, no element to the left is larger than x.
                # Therefore, x will never be removed.
                current_steps = 0
            
            # Update the global maximum steps.
            max_steps = max(max_steps, current_steps)
            # Push the current element and its calculated removal time onto the stack.
            stack.append((x, current_steps))
            
        return max_steps
# @lc code=end