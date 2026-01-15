#
# @lc app=leetcode id=3739 lang=python3
#
# [3739] Count Subarrays With Majority Element II
#

from typing import List

# @lc code=start
class Solution:
    def countMajoritySubarrays(self, nums: List[int], target: int) -> int:
        n = len(nums)
        # transform nums into +1/-1 array
        arr = [1 if x == target else -1 for x in nums]
        
        # compute prefix sums
        pref = [0] * (n + 1)
        for i in range(n):
            pref[i + 1] = pref[i] + arr[i]
        
        # coordinate compression
        sorted_vals = sorted(set(pref))
        rank_map = {val: idx + 1 for idx, val in enumerate(sorted_vals)}   # 1-indexed
        m = len(sorted_vals)
        
        # Fenwick tree
        bit = [0] * (m + 2)
        
        def update(idx: int, delta: int):
            while idx <= m:
                bit[idx] += delta
                idx += idx & -idx
        
        def query(idx: int) -> int:
            s = 0
            while idx > 0:
                s += bit[idx]
                idx -= idx & -idx
            return s
        
        ans = 0
        # insert first prefix sum
        update(rank_map[pref[0]], 1)
        
        for i in range(1, n + 1):
            v = pref[i]
            r = rank_map[v]
            # count previous prefix sums strictly less than v
            cnt = query(r - 1)
            ans += cnt
            update(r, 1)
        
        return ans
# @lc code=end