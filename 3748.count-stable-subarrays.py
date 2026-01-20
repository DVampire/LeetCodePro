#
# @lc app=leetcode id=3748 lang=python3
#
# [3748] Count Stable Subarrays
#

# @lc code=start
from typing import List


class Solution:
    def countStableSubarrays(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        n = len(nums)
        if n == 0:
            return []
        left = [0] * n
        for i in range(1, n):
            if nums[i - 1] <= nums[i]:
                left[i] = left[i - 1]
            else:
                left[i] = i
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] + left[i]
        
        def range_sum(l: int, r: int) -> int:
            def s(x: int) -> int:
                return x * (x + 1) // 2
            return s(r) - s(l - 1)
        
        ans = []
        for l, r in queries:
            m = r - l + 1
            triangle = m * (m + 1) // 2
            # Binary search for j0: smallest j >= l with left[j] > l
            lo = l
            hi = r + 1
            while lo < hi:
                mid = (lo + hi) // 2
                if left[mid] > l:
                    hi = mid
                else:
                    lo = mid + 1
            j0 = lo
            if j0 > r:
                res = triangle
            else:
                num_bad = r - j0 + 1
                sum_left_bad = prefix[r + 1] - prefix[j0]
                sum_max = l * (m - num_bad) + sum_left_bad
                sum_jp1 = range_sum(l, r) + m
                res = sum_jp1 - sum_max
            ans.append(res)
        return ans

# @lc code=end
