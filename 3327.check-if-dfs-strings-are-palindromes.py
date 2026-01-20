#
# @lc app=leetcode id=3327 lang=python3
#
# [3327] Check if DFS Strings Are Palindromes
#

from typing import List

import sys

# @lc code=start
class Solution:
    def findAnswer(self, parent: List[int], s: str) -> List[bool]:
        n = len(parent)
        children: List[List[int]] = [[] for _ in range(n)]
        for i in range(1, n):
            children[parent[i]].append(i)
        answer = [False] * n
        MOD1 = 1000000007
        MOD2 = 1000000009
        BASE1 = 131
        BASE2 = 137

        def dfs(u: int) -> tuple[int, int, int, int, int]:
            child_fwds1: list[int] = []
            child_fwds2: list[int] = []
            child_revs1: list[int] = []
            child_revs2: list[int] = []
            child_sizes: list[int] = []
            size = 1
            for c in children[u]:
                cf1, cf2, cr1, cr2, csz = dfs(c)
                child_fwds1.append(cf1)
                child_fwds2.append(cf2)
                child_revs1.append(cr1)
                child_revs2.append(cr2)
                child_sizes.append(csz)
                size += csz
            # forward hash 1
            h1 = 0
            for i in range(len(child_sizes)):
                p = pow(BASE1, child_sizes[i], MOD1)
                h1 = (h1 * p + child_fwds1[i]) % MOD1
            val = ord(s[u]) - ord('a') + 1
            p = pow(BASE1, 1, MOD1)
            h1 = (h1 * p + val) % MOD1
            fwd1 = h1
            # forward hash 2
            h2 = 0
            for i in range(len(child_sizes)):
                p = pow(BASE2, child_sizes[i], MOD2)
                h2 = (h2 * p + child_fwds2[i]) % MOD2
            p = pow(BASE2, 1, MOD2)
            h2 = (h2 * p + val) % MOD2
            fwd2 = h2
            # reverse hash 1
            r1 = val % MOD1
            for i in range(len(child_sizes) - 1, -1, -1):
                p = pow(BASE1, child_sizes[i], MOD1)
                r1 = (r1 * p + child_revs1[i]) % MOD1
            rev1 = r1
            # reverse hash 2
            r2 = val % MOD2
            for i in range(len(child_sizes) - 1, -1, -1):
                p = pow(BASE2, child_sizes[i], MOD2)
                r2 = (r2 * p + child_revs2[i]) % MOD2
            rev2 = r2
            answer[u] = (fwd1 == rev1) and (fwd2 == rev2)
            return fwd1, fwd2, rev1, rev2, size

        sys.setrecursionlimit(10**5 + 100)
        dfs(0)
        return answer

# @lc code=end
