#
# @lc app=leetcode id=3398 lang=python3
#
# [3398] Smallest Substring With Identical Characters I
#

# @lc code=start
class Solution:
    def minLength(self, s: str, numOps: int) -> int:
        n = len(s)

        def check(k: int) -> bool:
            if k == 1:
                # Case k=1: String must be alternating "0101..." or "1010..."
                flips01 = 0
                flips10 = 0
                for i in range(n):
                    val = int(s[i])
                    if val != (i % 2):
                        flips01 += 1
                    if val != ((i + 1) % 2):
                        flips10 += 1
                return min(flips01, flips10) <= numOps
            else:
                # Case k >= 2: Use greedy block breaking
                total_flips = 0
                count = 0
                for i in range(n):
                    count += 1
                    if i == n - 1 or s[i] != s[i + 1]:
                        total_flips += count // (k + 1)
                        count = 0
                return total_flips <= numOps

        # Binary search for the minimum possible max length k
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