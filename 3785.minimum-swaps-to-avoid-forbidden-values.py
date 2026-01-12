#
# @lc app=leetcode id=3785 lang=python3
#
# [3785] Minimum Swaps to Avoid Forbidden Values
#

# @lc code=start
from collections import Counter
from typing import List
import math

class Solution:
    def minSwaps(self, nums: List[int], forbidden: List[int]) -> int:
        n = len(nums)
        bad_indices = []
        for i in range(n):
            if nums[i] == forbidden[i]:
                bad_indices.append(i)
        
        if not bad_indices:
            return 0
            
        k = len(bad_indices)
        counts = Counter(nums[i] for i in bad_indices)
        max_val, max_freq = counts.most_common(1)[0]
        
        if max_freq <= k // 2:
            return (k + 1) // 2
        
        # If there's a majority value in bad positions, we need extra help from good positions
        needed = 2 * max_freq - k
        # Good positions are those where nums[i] != forbidden[i]
        # A good position i can help resolve a bad position of value max_val if:
        # 1. nums[i] != max_val
        # 2. forbidden[i] != max_val
        
        available_good = 0
        for i in range(n):
            if nums[i] != forbidden[i]:
                if nums[i] != max_val and forbidden[i] != max_val:
                    available_good += 1
        
        if available_good >= needed:
            return (k // 2) + (k % 2) + (needed - (k % 2) if needed > (k % 2) else 0)
            # Correct logic for majority case: 
            # We pair (k - max_freq) non-majority bads with (k - max_freq) majority bads.
            # Remaining majority bads: max_freq - (k - max_freq) = 2*max_freq - k = needed.
            # Each 'needed' bad requires 1 swap with a valid good position.
            return (k - max_freq) + needed
        
        return -1

# @lc code=end