#
# @lc app=leetcode id=3579 lang=python3
#
# [3579] Minimum Steps to Convert String with Operations
#

# @lc code=start
import sys
class Solution:
    def minOperations(self, word1: str, word2: str) -> int:
        n = len(word1)
        INF = 10**9 + 7
        dp = [INF] * (n + 1)
        dp[0] = 0

        def compute_no_reverse(l: int, r: int, rev_s: bool, rev_t: bool) -> int:
            k = r - l + 1
            cnt = [[0] * 26 for _ in range(26)]
            matches = 0
            a = ord('a')
            for ii in range(k):
                s_idx = r - ii if rev_s else l + ii
                s_ch = ord(word1[s_idx]) - a
                t_idx = r - ii if rev_t else l + ii
                t_ch = ord(word2[t_idx]) - a
                cnt[s_ch][t_ch] += 1
                if s_ch == t_ch:
                    matches += 1
            hamm = k - matches
            cross = 0
            for x in range(26):
                for y in range(x + 1, 26):
                    cross += min(cnt[x][y], cnt[y][x])
            return hamm - cross

        def min_ops_sub(l: int, r: int) -> int:
            c1 = compute_no_reverse(l, r, False, False)
            c2 = compute_no_reverse(l, r, True, False)
            c3 = compute_no_reverse(l, r, False, True)
            return min(c1, 1 + c2, 1 + c3)

        for i in range(1, n + 1):
            for j in range(i):
                cost = min_ops_sub(j, i - 1)
                if dp[j] + cost < dp[i]:
                    dp[i] = dp[j] + cost
        return dp[n]

# @lc code=end