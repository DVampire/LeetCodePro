#
# @lc app=leetcode id=3399 lang=python3
#
# [3399] Smallest Substring With Identical Characters II
#

# @lc code=start
class Solution:
    def minLength(self, s: str, numOps: int) -> int:
        n = len(s)
        
        # Pre-calculate block lengths for efficiency in check(k) where k >= 2
        blocks = []
        if n > 0:
            curr_len = 1
            for i in range(1, n):
                if s[i] == s[i-1]:
                    curr_len += 1
                else:
                    blocks.append(curr_len)
                    curr_len = 1
            blocks.append(curr_len)

        def check(k: int) -> bool:
            if k == 1:
                # Special case for k=1: must be alternating 0101... or 1010...
                flips0 = 0 # target 0101...
                flips1 = 0 # target 1010...
                for i in range(n):
                    # target0: index i should be i % 2
                    if int(s[i]) != (i % 2):
                        flips0 += 1
                    else:
                        flips1 += 1
                return min(flips0, flips1) <= numOps
            else:
                # General case for k >= 2: sum of floor(L / (k+1))
                total_flips = 0
                for length in blocks:
                    total_flips += length // (k + 1)
                return total_flips <= numOps

        # Binary search for the minimum k
        low = 1
        high = n
        ans = n
        
        while low <= high:
            mid = (low + high) // 2
            if check(mid):
                ans = mid
                high = mid - 1
            else:
                low = mid + 1
        
        return ans
# @lc code=end