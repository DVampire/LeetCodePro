#
# @lc app=leetcode id=3350 lang=python3
#
# [3350] Adjacent Increasing Subarrays Detection II
#

# @lc code=start
class Solution:
    def maxIncreasingSubarrays(self, nums: List[int]) -> int:
        n = len(nums)
        if n < 2:
            return 0
        
        max_k = 0
        prev_len = 0
        curr_len = 1
        
        for i in range(1, n):
            if nums[i] > nums[i-1]:
                # Continue the current strictly increasing segment
                curr_len += 1
            else:
                # A segment has ended. Process it.
                # Case 1: Two adjacent subarrays within the same segment
                max_k = max(max_k, curr_len // 2)
                # Case 2: Two adjacent subarrays spanning two segments
                if prev_len > 0:
                    max_k = max(max_k, min(prev_len, curr_len))
                
                # Prepare for the next segment
                prev_len = curr_len
                curr_len = 1
        
        # Process the final segment after the loop ends
        max_k = max(max_k, curr_len // 2)
        if prev_len > 0:
            max_k = max(max_k, min(prev_len, curr_len))
            
        return max_k
# @lc code=end