#
# @lc app=leetcode id=3399 lang=python3
#
# [3399] Smallest Substring With Identical Characters II
#

# @lc code=start
class Solution:
    def minLength(self, s: str, numOps: int) -> int:
        n = len(s)
        
        # Compute runs
        runs = []
        i = 0
        while i < n:
            j = i
            while j < n and s[j] == s[i]:
                j += 1
            runs.append(j - i)
            i = j
        
        # Check if max length L is achievable with at most numOps flips
        def canAchieve(L):
            if L == 1:
                # Need alternating pattern
                # Pattern "010101...": s[i] should be str(i % 2)
                cost1 = sum(1 for i in range(n) if s[i] != str(i % 2))
                cost2 = n - cost1
                return min(cost1, cost2) <= numOps
            else:
                # For each run of length r, need r // (L + 1) flips
                total_flips = sum(r // (L + 1) for r in runs)
                return total_flips <= numOps
        
        # Binary search
        lo, hi = 1, max(runs)
        while lo < hi:
            mid = (lo + hi) // 2
            if canAchieve(mid):
                hi = mid
            else:
                lo = mid + 1
        return lo
# @lc code=end