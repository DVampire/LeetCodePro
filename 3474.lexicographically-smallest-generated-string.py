#
# @lc app=leetcode id=3474 lang=python3
#
# [3474] Lexicographically Smallest Generated String
#

# @lc code=start
class Solution:
    def generateString(self, str1: str, str2: str) -> str:
        n, m = len(str1), len(str2)
        L = n + m - 1

        w = ['?'] * L
        forced = [False] * L

        # Step 1: apply all 'T' constraints
        for i, tf in enumerate(str1):
            if tf == 'T':
                base = i
                for j, c in enumerate(str2):
                    idx = base + j
                    if w[idx] == '?' or w[idx] == c:
                        w[idx] = c
                        forced[idx] = True
                    else:
                        return ""

        # Step 2: fill remaining with 'a'
        for k in range(L):
            if w[k] == '?':
                w[k] = 'a'

        # Step 3: enforce 'F' constraints greedily (change rightmost free position to 'b')
        for i, tf in enumerate(str1):
            if tf == 'F':
                base = i
                equal = True
                for j, c in enumerate(str2):
                    if w[base + j] != c:
                        equal = False
                        break
                if equal:
                    pos = -1
                    for j in range(m - 1, -1, -1):
                        idx = base + j
                        if not forced[idx]:
                            pos = idx
                            break
                    if pos == -1:
                        return ""
                    w[pos] = 'b'

        # Step 4: final verification (optional but safe)
        for i, tf in enumerate(str1):
            base = i
            if tf == 'T':
                for j, c in enumerate(str2):
                    if w[base + j] != c:
                        return ""
            else:  # 'F'
                eq = True
                for j, c in enumerate(str2):
                    if w[base + j] != c:
                        eq = False
                        break
                if eq:
                    return ""

        return "".join(w)
# @lc code=end
