#
# @lc app=leetcode id=3504 lang=python3
#
# [3504] Longest Palindrome After Substring Concatenation II
#

# @lc code=start
class Solution:
    def longestPalindrome(self, s: str, t: str) -> int:
        max_len = 0
        
        # Try all possible concatenations of substrings
        for i in range(len(s) + 1):
            for j in range(i, len(s) + 1):
                for k in range(len(t) + 1):
                    for l in range(k, len(t) + 1):
                        concat = s[i:j] + t[k:l]
                        # Only check if potentially longer than current max
                        if len(concat) > max_len and concat == concat[::-1]:
                            max_len = len(concat)
        
        return max_len
# @lc code=end