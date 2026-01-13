#
# @lc app=leetcode id=3434 lang=python3
#
# [3434] Maximum Frequency After Subarray Operation
#
# @lc code=start
class Solution:
    def maxFrequency(self, nums: List[int], k: int) -> int:
        base_count = nums.count(k)
        max_freq = base_count
        
        # Try all possible target values (elements we want to convert to k)
        for target in range(1, 51):
            if target == k:
                continue
            
            # Find maximum subarray gain using Kadane's algorithm
            max_gain = 0
            current_sum = 0
            for num in nums:
                gain = 0
                if num == target:
                    gain = 1  # Convert target to k
                elif num == k:
                    gain = -1  # Lose a k
                
                current_sum = max(gain, current_sum + gain)
                max_gain = max(max_gain, current_sum)
            
            # Update maximum frequency
            max_freq = max(max_freq, base_count + max_gain)
        
        return max_freq
# @lc code=end