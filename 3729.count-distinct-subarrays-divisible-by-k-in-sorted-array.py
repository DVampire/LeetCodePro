#
# @lc app=leetcode id=3729 lang=python3
#
# [3729] Count Distinct Subarrays Divisible by K in Sorted Array
#
# @lc code=start
class Solution:
    def numGoodSubarrays(self, nums: List[int], k: int) -> int:
        distinct_subarrays = set()
        n = len(nums)
        
        for i in range(n):
            current_sum = 0
            for j in range(i, n):
                current_sum += nums[j]
                if current_sum % k == 0:
                    distinct_subarrays.add(tuple(nums[i:j+1]))
        
        return len(distinct_subarrays)
# @lc code=end