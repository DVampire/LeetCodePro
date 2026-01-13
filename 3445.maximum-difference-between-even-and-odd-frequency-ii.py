#
# @lc app=leetcode id=3445 lang=python3
#
# [3445] Maximum Difference Between Even and Odd Frequency II
#

# @lc code=start
from typing import *

class Solution:
    def maxDifference(self, s: str, k: int) -> int:
        n = len(s)
        digits = [ord(ch) - 48 for ch in s]  # 0..4

        # pref[c][i] = count of digit c in s[:i]
        pref = [[0] * (n + 1) for _ in range(5)]
        cnt = [0] * 5
        for i, d in enumerate(digits, 1):
            cnt[d] += 1
            for c in range(5):
                pref[c][i] = cnt[c]

        INF = 10**9
        ans = -INF

        for a in range(5):
            for b in range(5):
                if a == b:
                    continue
                PA = pref[a]
                PB = pref[b]

                # best[paParity][pbParity] = min(PA[l]-PB[l]) among eligible l
                best = [[INF, INF], [INF, INF]]

                p_added = 0  # next l index to add into best
                q = -1        # max index with PB[index] <= PB[r]-2 (moves monotonically)

                for r in range(n + 1):
                    pb_limit = PB[r] - 2
                    while q + 1 <= n and PB[q + 1] <= pb_limit:
                        q += 1

                    bound = min(r - k, q)
                    while p_added <= bound:
                        pa_p = PA[p_added] & 1
                        pb_p = PB[p_added] & 1
                        dval = PA[p_added] - PB[p_added]
                        if dval < best[pa_p][pb_p]:
                            best[pa_p][pb_p] = dval
                        p_added += 1

                    pa_need = (PA[r] & 1) ^ 1
                    pb_need = PB[r] & 1
                    min_d = best[pa_need][pb_need]
                    if min_d != INF:
                        cand = (PA[r] - PB[r]) - min_d
                        if cand > ans:
                            ans = cand

        return ans
# @lc code=end
