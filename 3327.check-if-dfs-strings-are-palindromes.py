#
# @lc app=leetcode id=3327 lang=python3
#
# [3327] Check if DFS Strings Are Palindromes
#

from typing import List

# @lc code=start
class Solution:
    def findAnswer(self, parent: List[int], s: str) -> List[bool]:
        n = len(parent)
        children = [[] for _ in range(n)]
        for i in range(1, n):
            children[parent[i]].append(i)  # appended in increasing i => already sorted

        start = [0] * n
        end = [0] * n
        post_chars: List[str] = []

        # Iterative DFS to generate postorder sequence and subtree segments.
        # state 0 = enter, state 1 = exit
        stack = [(0, 0)]
        while stack:
            u, st = stack.pop()
            if st == 0:
                start[u] = len(post_chars)
                stack.append((u, 1))
                # push children in reverse so they are processed in increasing order
                for v in reversed(children[u]):
                    stack.append((v, 0))
            else:
                post_chars.append(s[u])
                end[u] = len(post_chars) - 1

        T = ''.join(post_chars)
        Tr = T[::-1]

        mod1, mod2 = 1_000_000_007, 1_000_000_009
        base = 911382323

        pow1 = [1] * (n + 1)
        pow2 = [1] * (n + 1)
        for i in range(1, n + 1):
            pow1[i] = (pow1[i - 1] * base) % mod1
            pow2[i] = (pow2[i - 1] * base) % mod2

        def build_prefix(t: str, mod: int) -> List[int]:
            pref = [0] * (n + 1)
            for i, ch in enumerate(t):
                x = ord(ch) - 96  # 1..26
                pref[i + 1] = (pref[i] * base + x) % mod
            return pref

        pref1 = build_prefix(T, mod1)
        pref2 = build_prefix(T, mod2)
        pref1r = build_prefix(Tr, mod1)
        pref2r = build_prefix(Tr, mod2)

        def get_hash(pref: List[int], l: int, r: int, pw: List[int], mod: int) -> int:
            # inclusive l..r
            return (pref[r + 1] - (pref[l] * pw[r - l + 1]) % mod) % mod

        ans = [False] * n
        for i in range(n):
            l, r = start[i], end[i]
            rl, rr = n - 1 - r, n - 1 - l

            h1 = get_hash(pref1, l, r, pow1, mod1)
            h1r = get_hash(pref1r, rl, rr, pow1, mod1)
            if h1 != h1r:
                continue

            h2 = get_hash(pref2, l, r, pow2, mod2)
            h2r = get_hash(pref2r, rl, rr, pow2, mod2)
            ans[i] = (h2 == h2r)

        return ans
# @lc code=end
