#
# @lc app=leetcode id=3739 lang=python3
#
# [3739] Count Subarrays With Majority Element II
#

# @lc code=start
from typing import List

class Solution:
    def countMajoritySubarrays(self, nums: List[int], target: int) -> int:
        n = len(nums)
        a = [1 if num == target else -1 for num in nums]
        prefix = [0] * (n + 1)
        for i in range(1, n + 1):
            prefix[i] = prefix[i - 1] + a[i - 1]
        OFFSET = n + 1
        SIZE = 2 * n + 2
        tree = [0] * (SIZE + 1)
        
        def update(idx: int, val: int) -> None:
            while idx <= SIZE:
                tree[idx] += val
                idx += idx & -idx
        
        def query(idx: int) -> int:
            res = 0
            while idx > 0:
                res += tree[idx]
                idx -= idx & -idx
            return res
        
        ans = 0
        update(prefix[0] + OFFSET, 1)
        for r in range(1, n + 1):
            ans += query(prefix[r] + OFFSET - 1)
            update(prefix[r] + OFFSET, 1)
        return ans
# @lc code=end
