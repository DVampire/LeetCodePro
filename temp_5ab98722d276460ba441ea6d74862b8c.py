#
# @lc app=leetcode id=3347 lang=python3
#
# [3347] Maximum Frequency of an Element After Performing Operations II
#

# @lc code=start
from collections import Counter

class Solution:
    def maxFrequency(self, nums: List[int], k: int, numOperations: int) -> int:
        nums.sort()
        n = len(nums)
        
        # Case 1: x is NOT in nums (or we don't care about its frequency in nums)
        # We want to maximize min(count(nums in [x-k, x+k]), numOperations)
        # The max count of nums in any interval of length 2k is found by sliding window.
        max_c = 0
        l = 0
        for r in range(n):
            while nums[r] - nums[l] > 2 * k:
                l += 1
            max_c = max(max_c, r - l + 1)
        
        ans = min(max_c, numOperations)
        
        # Case 2: x IS in nums
        # We want to maximize min(count(nums in [x-k, x+k]), freq(x) + numOperations)
        counts = Counter(nums)
        unique_nums = sorted(counts.keys())
        
        l = 0
        r = 0
        for u in unique_nums:
            # Find range [u-k, u+k] in sorted nums
            while nums[l] < u - k:
                l += 1
            while r < n and nums[r] <= u + k:
                r += 1
            
            total_in_range = r - l
            ans = max(ans, min(total_in_range, counts[u] + numOperations))
            
        return ans
# @lc code=end