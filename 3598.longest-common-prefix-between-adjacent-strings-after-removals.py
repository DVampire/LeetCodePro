#
# @lc app=leetcode id=3598 lang=python3
#
# [3598] Longest Common Prefix Between Adjacent Strings After Removals
#

from typing import List

# @lc code=start
class Solution:
    def longestCommonPrefix(self, words: List[str]) -> List[int]:
        n = len(words)

        def lcp_len(a: str, b: str) -> int:
            L = min(len(a), len(b))
            i = 0
            while i < L and a[i] == b[i]:
                i += 1
            return i

        # lcp between original adjacent pairs
        m = n - 1
        lcp = [0] * max(0, m)
        for j in range(m):
            lcp[j] = lcp_len(words[j], words[j + 1])

        if m <= 0:
            return [0] * n

        # prefix and suffix maxima for lcp array
        pref = [0] * m
        cur = 0
        for j in range(m):
            cur = max(cur, lcp[j])
            pref[j] = cur

        suf = [0] * m
        cur = 0
        for j in range(m - 1, -1, -1):
            cur = max(cur, lcp[j])
            suf[j] = cur

        ans = [0] * n
        for i in range(n):
            best = 0

            # unchanged pairs on the left: lcp[0 .. i-2]
            left_idx = i - 2
            if left_idx >= 0:
                best = max(best, pref[left_idx])

            # unchanged pairs on the right: lcp[i+1 .. m-1]
            right_idx = i + 1
            if right_idx <= m - 1:
                best = max(best, suf[right_idx])

            # new bridged pair (i-1, i+1)
            if 0 <= i - 1 and i + 1 < n:
                best = max(best, lcp_len(words[i - 1], words[i + 1]))

            ans[i] = best

        return ans
# @lc code=end
