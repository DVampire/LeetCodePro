#
# @lc app=leetcode id=3420 lang=python3
#
# [3420] Count Non-Decreasing Subarrays After K Operations
#

# @lc code=start
from collections import deque
from typing import List

class Solution:
    def countNonDecreasingSubarrays(self, nums: List[int], k: int) -> int:
        n = len(nums)
        result = 0
        dq = deque()  # monotonic decreasing deque of indices (by value)
        cost = 0
        
        r = n
        for l in range(n - 1, -1, -1):
            # Add l to the window [l, r-1]
            # Merge pillars with values <= nums[l]
            while dq and nums[dq[0]] <= nums[l]:
                old_pillar = dq.popleft()
                next_pos = dq[0] if dq else r
                count = next_pos - old_pillar
                cost += (nums[l] - nums[old_pillar]) * count
            dq.appendleft(l)
            
            # Shrink from the right if cost > k
            while r > l and cost > k:
                r -= 1
                # Remove element at position r
                cost -= nums[dq[-1]] - nums[r]
                if dq[-1] == r:
                    dq.pop()
            
            result += r - l
        
        return result
# @lc code=end