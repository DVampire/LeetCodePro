#
# @lc app=leetcode id=3504 lang=python3
#
# [3504] Longest Palindrome After Substring Concatenation II
#

# @lc code=start
import typing

class RollingHash:
    def __init__(self, s: str, base: int = 31, mod1: int = 10**9 + 7, mod2: int = 10**9 + 9):
        self.n = len(s)
        self.base = base
        self.mod1 = mod1
        self.mod2 = mod2
        self.p1 = [1] * (self.n + 1)
        self.p2 = [1] * (self.n + 1)
        self.h1 = [0] * (self.n + 1)
        self.h2 = [0] * (self.n + 1)
        for i in range(1, self.n + 1):
            self.p1[i] = self.p1[i - 1] * base % mod1
            self.p2[i] = self.p2[i - 1] * base % mod2
            val = ord(s[i - 1]) - ord('a') + 1
            self.h1[i] = (self.h1[i - 1] * base + val) % mod1
            self.h2[i] = (self.h2[i - 1] * base + val) % mod2

    def get(self, l: int, r: int) -> tuple[int, int]:
        len_ = r - l
        h1 = (self.h1[r] - self.h1[l] * self.p1[len_] % self.mod1 + self.mod1) % self.mod1
        h2 = (self.h2[r] - self.h2[l] * self.p2[len_] % self.mod2 + self.mod2) % self.mod2
        return (h1, h2)

class Solution:
    def longestPalindrome(self, s: str, t: str) -> int:
        ns, nt = len(s), len(t)

        # DP for palindromes in s
        pal_s = [[False] * ns for _ in range(ns)]
        for i in range(ns):
            pal_s[i][i] = True
        for i in range(ns - 1):
            if s[i] == s[i + 1]:
                pal_s[i][i + 1] = True
        for length in range(3, ns + 1):
            for i in range(ns - length + 1):
                j = i + length - 1
                if s[i] == s[j] and pal_s[i + 1][j - 1]:
                    pal_s[i][j] = True

        # DP for palindromes in t
        pal_t = [[False] * nt for _ in range(nt)]
        for i in range(nt):
            pal_t[i][i] = True
        for i in range(nt - 1):
            if t[i] == t[i + 1]:
                pal_t[i][i + 1] = True
        for length in range(3, nt + 1):
            for i in range(nt - length + 1):
                j = i + length - 1
                if t[i] == t[j] and pal_t[i + 1][j - 1]:
                    pal_t[i][j] = True

        # max_pal_prefix_s
        max_pal_prefix_s = [0] * (ns + 1)
        for i in range(ns):
            for j in range(i, ns):
                if pal_s[i][j]:
                    max_pal_prefix_s[i] = max(max_pal_prefix_s[i], j - i + 1)

        # max_pal_prefix_t
        max_pal_prefix_t = [0] * (nt + 1)
        for i in range(nt):
            for j in range(i, nt):
                if pal_t[i][j]:
                    max_pal_prefix_t[i] = max(max_pal_prefix_t[i], j - i + 1)

        # max_pal_suffix_t
        max_pal_suffix_t = [0] * nt
        for end_pos in range(nt):
            for st in range(end_pos + 1):
                if pal_t[st][end_pos]:
                    l = end_pos - st + 1
                    max_pal_suffix_t[end_pos] = max(max_pal_suffix_t[end_pos], l)

        max_len = 0
        for i in range(ns):
            max_len = max(max_len, max_pal_prefix_s[i])
        for i in range(nt):
            max_len = max(max_len, max_pal_prefix_t[i])

        # Rolling hashes
        rs = s[::-1]
        rt = t[::-1]
        hash_s = RollingHash(s)
        hash_rs = RollingHash(rs)
        hash_t = RollingHash(t)
        hash_rt = RollingHash(rt)

        # Case 1: len(A) >= len(B) = k
        for k in range(1, ns + 1):
            t_set_k = set()
            for p in range(nt - k + 1):
                h = hash_t.get(p, p + k)
                t_set_k.add(h)
            for i in range(ns - k + 1):
                rev_l = ns - (i + k)
                rev_r = ns - i
                h = hash_rs.get(rev_l, rev_r)
                if h in t_set_k:
                    start_c = i + k
                    len_c = max_pal_prefix_s[start_c]
                    total = 2 * k + len_c
                    max_len = max(max_len, total)

        # Case 2: len(B) >= len(A) = k
        for k in range(1, nt + 1):
            s_set_k = set()
            for p in range(ns - k + 1):
                h = hash_s.get(p, p + k)
                s_set_k.add(h)
            for j in range(nt - k + 1):
                rev_l = nt - (j + k)
                rev_r = nt - j
                h = hash_rt.get(rev_l, rev_r)
                if h in s_set_k:
                    end_d = j - 1
                    len_d = max_pal_suffix_t[end_d] if end_d >= 0 else 0
                    total = 2 * k + len_d
                    max_len = max(max_len, total)

        return max_len

# @lc code=end
