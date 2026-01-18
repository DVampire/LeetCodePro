#
# @lc app=leetcode id=2289 lang=python3
#
# [2289] Steps to Make Array Non-decreasing
#

# @lc code=start
class Solution:
    def totalSteps(self, nums: List[int]) -> int:
        n = len(nums)
        dp = [0] * n
        stack = []
        ans = 0
        
        for i in range(n):
            cur_max_steps = 0
            # While the stack is not empty and the current element is greater than or equal to
            # the element at the top of the stack, it means the current element survives longer
            # than the elements it's 'swallowing'.
            while stack and nums[stack[-1]] <= nums[i]:
                # The current element nums[i] can only be removed after the element we just popped
                # is removed. So we track the maximum steps it took for the popped elements to be removed.
                cur_max_steps = max(cur_max_steps, dp[stack.pop()])
            
            # If the stack is not empty, it means there is an element to the left (nums[stack[-1]])
            # that is strictly greater than nums[i]. This element will eventually 'remove' nums[i].
            if stack:
                # nums[i] is removed one step after all the elements in between (that were swallowed)
                # are removed.
                dp[i] = cur_max_steps + 1
            else:
                # No element to the left is greater than nums[i], so it will never be removed.
                dp[i] = 0
            
            stack.append(i)
            ans = max(ans, dp[i])
            
        return ans
# @lc code=end