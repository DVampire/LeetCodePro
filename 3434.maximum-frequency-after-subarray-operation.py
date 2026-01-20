#
# @lc app=leetcode id=3434 lang=python3
#
# [3434] Maximum Frequency After Subarray Operation
#

# @lc code=start
class Solution:
    def maxFrequency(self, nums: List[int], k: int) -> int:
        total_k = 0
        for x in nums:
            if x == k:
                total_k += 1
        
        max_gain = 0
        
        # The constraints say nums[i] <= 50. We can iterate over all possible
        # target values that we want to convert to k.
        # Let's say we want to convert value `v` to `k`.
        # We treat `v` as +1 and `k` as -1 in a subarray to maximize the gain.
        
        # Optimization: only consider values actually present in nums
        unique_elements = set(nums)
        if k in unique_elements:
            unique_elements.remove(k)
            
        for v in unique_elements:
            current_gain = 0
            max_v_gain = 0
            for x in nums:
                if x == v:
                    current_gain += 1
                elif x == k:
                    current_gain -= 1
                
                if current_gain < 0:
                    current_gain = 0
                
                if current_gain > max_v_gain:
                    max_v_gain = current_gain
            
            if max_v_gain > max_gain:
                max_gain = max_v_gain
                
        return total_k + max_gain
# @lc code=end