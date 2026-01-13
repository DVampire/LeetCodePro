#
# @lc app=leetcode id=3399 lang=python3
#
# [3399] Smallest Substring With Identical Characters II
#

# @lc code=start
class Solution:
    def minLength(self, s: str, numOps: int) -> int:
        n = len(s)
        
        def ops_for_alternating():
            # Pattern starting with '0'
            ops0 = sum(1 for i in range(n) if s[i] != ('0' if i % 2 == 0 else '1'))
            # Pattern starting with '1'
            ops1 = sum(1 for i in range(n) if s[i] != ('1' if i % 2 == 0 else '0'))
            return min(ops0, ops1)
        
        def can_achieve(max_len):
            if max_len == 1:
                return ops_for_alternating() <= numOps
            
            # For max_len > 1, use block-based approach
            ops = 0
            i = 0
            while i < n:
                j = i
                while j < n and s[j] == s[i]:
                    j += 1
                length = j - i
                if length > max_len:
                    ops += length // (max_len + 1)
                i = j
            return ops <= numOps
        
        # Binary search on the answer
        left, right = 1, n
        result = n
        
        while left <= right:
            mid = (left + right) // 2
            if can_achieve(mid):
                result = mid
                right = mid - 1
            else:
                left = mid + 1
        
        return result
# @lc code=end