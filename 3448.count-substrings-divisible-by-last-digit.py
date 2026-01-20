#
# @lc app=leetcode id=3448 lang=python3
#
# [3448] Count Substrings Divisible By Last Digit
#

# @lc code=start
class Solution:
    def countSubstrings(self, s: str) -> int:
        n = len(s)
        ans = 0
        freqs = [[0] * dd for dd in range(1, 10)]
        for j in range(n):
            digit = int(s[j])
            for ddi in range(9):
                dd = ddi + 1
                f = freqs[ddi]
                new_f = [0] * dd
                for rem in range(dd):
                    newr = (rem * 10 + digit) % dd
                    new_f[newr] += f[rem]
                single_r = digit % dd
                new_f[single_r] += 1
                if digit == dd:
                    ans += new_f[0]
                freqs[ddi] = new_f
        return ans

# @lc code=end