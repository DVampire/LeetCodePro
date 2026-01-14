#
# @lc app=leetcode id=3398 lang=python3
#
# [3398] Smallest Substring With Identical Characters I
#

# @lc code=start
class Solution:
    def minLength(self, s: str, numOps: int) -> int:
        n = len(s)
        
        def canAchieve(L):
            if L == 1:
                # Count differences from alternating patterns
                diff1 = sum(1 for i, c in enumerate(s) if int(c) != i % 2)
                diff2 = sum(1 for i, c in enumerate(s) if int(c) != (i + 1) % 2)
                return min(diff1, diff2) <= numOps
            else:
                # For each run, count flips needed
                ops = 0
                i = 0
                while i < n:
                    j = i
                    while j < n and s[j] == s[i]:
                        j += 1
                    run_len = j - i
                    ops += run_len // (L + 1)
                    i = j
                return ops <= numOps
        
        # Binary search for the minimum achievable L
        left, right = 1, n
        while left < right:
            mid = (left + right) // 2
            if canAchieve(mid):
                right = mid
            else:
                left = mid + 1
        
        return left
# @lc code=end