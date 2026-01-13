#
# @lc app=leetcode id=3420 lang=python3
#
# [3420] Count Non-Decreasing Subarrays After K Operations
#
# @lc code=start
class Solution:
    def countNonDecreasingSubarrays(self, nums: List[int], k: int) -> int:
        n = len(nums)
        count = 0
        
        for left in range(n):
            running_max = nums[left]
            operations = 0
            for right in range(left, n):
                operations += max(0, running_max - nums[right])
                running_max = max(running_max, nums[right])
                if operations <= k:
                    count += 1
                else:
                    break
        
        return count
# @lc code=end