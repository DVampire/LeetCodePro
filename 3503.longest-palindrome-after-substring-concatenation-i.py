#
# @lc app=leetcode id=3503 lang=python3
#
# [3503] Longest Palindrome After Substring Concatenation I
#

# @lc code=start
class Solution:
    def longestPalindrome(self, s: str, t: str) -> int:
        n = len(s)
        m = len(t)
        max_len = 0
        
        # Iterate over all substrings of s (including empty)
        for i in range(n + 1):
            for j in range(i, n + 1):
                sub_s = s[i:j]
                
                # Iterate over all substrings of t (including empty)
                for k in range(m + 1):
                    for l in range(k, m + 1):
                        sub_t = t[k:l]
                        
                        combined = sub_s + sub_t
                        
                        # Check if palindrome
                        if combined == combined[::-1]:
                            max_len = max(max_len, len(combined))
                            
        return max_len
# @lc code=end