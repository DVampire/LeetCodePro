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
        
        # For each starting position
        for i in range(n):
            cost = 0
            max_so_far = nums[i]
            
            # Extend ending position as far as possible
            for j in range(i, n):
                if nums[j] < max_so_far:
                    cost += max_so_far - nums[j]
                else:
                    max_so_far = nums[j]
                
                if cost <= k:
                    count += 1
                else:
                    break
        
        return count
# @lc code=end