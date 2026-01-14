#
# @lc app=leetcode id=3503 lang=python3
#
# [3503] Longest Palindrome After Substring Concatenation I
#
# @lc code=start
class Solution:
    def longestPalindrome(self, s: str, t: str) -> int:
        def is_palindrome(string):
            return string == string[::-1]
        
        max_len = 0
        n, m = len(s), len(t)
        
        for i in range(n + 1):
            for j in range(i, n + 1):
                for k in range(m + 1):
                    for l in range(k, m + 1):
                        combined = s[i:j] + t[k:l]
                        if is_palindrome(combined) and len(combined) > max_len:
                            max_len = len(combined)
        
        return max_len
# @lc code=end