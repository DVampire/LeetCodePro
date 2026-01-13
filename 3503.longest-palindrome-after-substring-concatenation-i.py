#
# @lc app=leetcode id=3503 lang=python3
#
# [3503] Longest Palindrome After Substring Concatenation I
#

# @lc code=start
class Solution:
    def longestPalindrome(self, s: str, t: str) -> int:
        def all_substrings(x: str):
            n = len(x)
            subs = [""]
            for i in range(n):
                for j in range(i + 1, n + 1):
                    subs.append(x[i:j])
            return subs

        def is_pal(x: str) -> bool:
            i, j = 0, len(x) - 1
            while i < j:
                if x[i] != x[j]:
                    return False
                i += 1
                j -= 1
            return True

        subs_s = all_substrings(s)
        subs_t = all_substrings(t)

        subs_s.sort(key=len, reverse=True)
        subs_t.sort(key=len, reverse=True)

        max_t_len = len(subs_t[0])
        best = 0

        for a in subs_s:
            la = len(a)
            if la + max_t_len <= best:
                break
            for b in subs_t:
                total = la + len(b)
                if total <= best:
                    break
                if is_pal(a + b):
                    best = total
                    break

        return best
# @lc code=end
