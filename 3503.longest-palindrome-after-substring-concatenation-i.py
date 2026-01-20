#
# @lc app=leetcode id=3503 lang=python3
#
# [3503] Longest Palindrome After Substring Concatenation I
#

# @lc code=start
class Solution:
    def longestPalindrome(self, s: str, t: str) -> int:
        max_len = 0
        ns, nt = len(s), len(t)
        for si in range(ns + 1):
            for sj in range(si, ns + 1):
                lens = sj - si
                for ti in range(nt + 1):
                    for tj in range(ti, nt + 1):
                        lent = tj - ti
                        tot = lens + lent
                        if tot <= max_len:
                            continue
                        concat = s[si:sj] + t[ti:tj]
                        if concat == concat[::-1]:
                            max_len = tot
        return max_len
# @lc code=end