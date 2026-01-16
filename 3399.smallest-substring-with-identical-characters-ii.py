#
# @lc app=leetcode id=3399 lang=python3
#
# [3399] Smallest Substring With Identical Characters II
#

# @lc code=start
class Solution:
    def minLength(self, s: str, numOps: int) -> int:
        n = len(s)
        # Binary search on the answer
        def canAchieve(maxLen: int) -> bool:
            # For each segment of same characters, we want to break it into pieces of length at most maxLen
            # We need to count how many operations are needed
            ops = 0
            i = 0
            while i < n:
                j = i
                while j < n and s[j] == s[i]:
                    j += 1
                # s[i..j-1] is a segment of same characters
                length = j - i
                if length > maxLen:
                    # We need to break this segment
                    # Number of breaks needed = length // (maxLen + 1)
                    # Because each piece can be at most maxLen long
                    breaks = (length - 1) // maxLen
                    ops += breaks
                i = j
            return ops <= numOps
        
        # Binary search for the minimum possible maxLen
        left, right = 1, n
        answer = n
        while left <= right:
            mid = (left + right) // 2
            if canAchieve(mid):
                answer = mid
                right = mid - 1
            else:
                left = mid + 1
        return answer
# @lc code=end