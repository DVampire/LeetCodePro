#
# @lc app=leetcode id=3398 lang=python3
#
# [3398] Smallest Substring With Identical Characters I
#

# @lc code=start
class Solution:
    def minLength(self, s: str, numOps: int) -> int:
        n = len(s)
        
        # Special case for k=1: check if we can make the string alternating
        def canMakeAlternating():
            mismatches1 = sum(1 for i in range(n) if s[i] != ('0' if i % 2 == 0 else '1'))
            mismatches2 = sum(1 for i in range(n) if s[i] != ('1' if i % 2 == 0 else '0'))
            return min(mismatches1, mismatches2) <= numOps
        
        if canMakeAlternating():
            return 1
        
        # Find all runs of identical characters
        runs = []
        i = 0
        while i < n:
            j = i
            while j < n and s[j] == s[i]:
                j += 1
            runs.append(j - i)
            i = j
        
        # Binary search on the answer (starting from 2)
        def canAchieve(k):
            flips_needed = 0
            for run_length in runs:
                if run_length > k:
                    flips_needed += run_length // (k + 1)
            return flips_needed <= numOps
        
        left, right = 2, max(runs)
        result = right
        
        while left <= right:
            mid = (left + right) // 2
            if canAchieve(mid):
                result = mid
                right = mid - 1
            else:
                left = mid + 1
        
        return result
# @lc code=end