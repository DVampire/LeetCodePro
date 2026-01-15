#
# @lc app=leetcode id=3729 lang=python3
#
# [3729] Count Distinct Subarrays Divisible by K in Sorted Array
#

# @lc code=start
class Solution:
    def numGoodSubarrays(self, nums: List[int], k: int) -> int:
        n = len(nums)
        
        # Compute prefix sums
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] + nums[i]
        
        from collections import defaultdict
        counter = defaultdict(int)
        added_up_to = -1  # We've added prefix[0], ..., prefix[added_up_to] to counter
        count = 0
        first_occurrence = 0  # First occurrence of the current value
        
        for j in range(n):
            # Update first_occurrence if nums[j] is different from nums[j-1]
            if j > 0 and nums[j] != nums[j - 1]:
                first_occurrence = j
            
            # Update counter to include prefix[0], ..., prefix[first_occurrence]
            while added_up_to < first_occurrence:
                added_up_to += 1
                counter[prefix[added_up_to] % k] += 1
            
            # Query for prefix[j+1] mod k
            r = prefix[j + 1] % k
            count += counter[r]
        
        return count
# @lc code=end