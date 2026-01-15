#
# @lc app=leetcode id=3605 lang=python3
#
# [3605] Minimum Stability Factor of Array
#

# @lc code=start
from typing import List
from math import gcd, log2, floor

class Solution:
    def minStable(self, nums: List[int], maxC: int) -> int:
        n = len(nums)
        if n == 0:
            return 0
        
        # Build sparse table for range GCD queries
        LOG = floor(log2(n)) + 1 if n > 1 else 1
        st = [[0] * n for _ in range(LOG)]
        st[0] = nums[:]
        
        for k in range(1, LOG):
            for i in range(n - (1 << k) + 1):
                st[k][i] = gcd(st[k-1][i], st[k-1][i + (1 << (k-1))])
        
        def query_gcd(l, r):
            if l > r:
                return 0
            length = r - l + 1
            k = floor(log2(length))
            return gcd(st[k][l], st[k][r - (1 << k) + 1])
        
        # Compute L[i] for each i using binary search
        # L[i] = minimum j such that GCD(nums[j:i+1]) >= 2
        L = [0] * n
        for i in range(n):
            if nums[i] < 2:
                L[i] = i + 1  # No stable subarray ending at i
            else:
                lo, hi = 0, i
                while lo < hi:
                    mid_j = (lo + hi) // 2
                    if query_gcd(mid_j, i) >= 2:
                        hi = mid_j
                    else:
                        lo = mid_j + 1
                L[i] = lo
        
        # Check if we can achieve stability factor <= mid with at most maxC modifications
        def check(mid):
            start = 0
            blocker_count = 0
            for i in range(n):
                if L[i] <= i:  # There's a stable subarray ending at i
                    length = i - max(L[i], start) + 1
                    if length > mid:
                        blocker_count += 1
                        if blocker_count > maxC:
                            return False
                        start = i + 1
            return True
        
        # Binary search on the answer
        lo, hi = 0, n
        while lo < hi:
            mid = (lo + hi) // 2
            if check(mid):
                hi = mid
            else:
                lo = mid + 1
        
        return lo
# @lc code=end