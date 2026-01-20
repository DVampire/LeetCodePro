#
# @lc app=leetcode id=3434 lang=python3
#
# [3434] Maximum Frequency After Subarray Operation
#

# @lc code=start
from typing import List

class Solution:
    def maxFrequency(self, nums: List[int], k: int) -> int:
        n = len(nums)
        total_k = nums.count(k)
        max_gain = 0
        for t in range(1, 51):
            # Kadane on the fly
            if n == 0:
                continue
            score = (1 if nums[0] == t else 0) - (1 if nums[0] == k else 0)
            max_ending = score
            max_so_far = score
            for i in range(1, n):
                score = (1 if nums[i] == t else 0) - (1 if nums[i] == k else 0)
                max_ending = max(score, max_ending + score)
                max_so_far = max(max_so_far, max_ending)
            max_gain = max(max_gain, max_so_far)
        return total_k + max_gain

# @lc code=end