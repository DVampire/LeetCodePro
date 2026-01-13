#
# @lc app=leetcode id=3579 lang=python3
#
# [3579] Minimum Steps to Convert String with Operations
#

# @lc code=start
class Solution:
    def minOperations(self, word1: str, word2: str) -> int:
        n = len(word1)

        def eval_cost(l: int, r: int, reversed_seg: bool) -> int:
            # cost using only swaps (disjoint) + replacements, given a fixed orientation
            cnt = [[0] * 26 for _ in range(26)]
            mismatches = 0
            m = r - l
            for t in range(m):
                c2 = word2[l + t]
                if not reversed_seg:
                    c1 = word1[l + t]
                else:
                    c1 = word1[r - 1 - t]
                if c1 != c2:
                    mismatches += 1
                    cnt[ord(c1) - 97][ord(c2) - 97] += 1

            beneficial = 0
            for a in range(26):
                rowa = cnt[a]
                for b in range(a + 1, 26):
                    x = rowa[b]
                    y = cnt[b][a]
                    beneficial += x if x < y else y

            return mismatches - beneficial

        # Precompute segment costs
        cost = [[0] * (n + 1) for _ in range(n)]
        for l in range(n - 1, -1, -1):
            for r in range(l + 1, n + 1):
                normal = eval_cost(l, r, False)
                rev = 1 + eval_cost(l, r, True)
                cost[l][r] = normal if normal < rev else rev

        # DP over partitions
        INF = 10 ** 9
        dp = [INF] * (n + 1)
        dp[0] = 0
        for i in range(1, n + 1):
            best = INF
            for j in range(i):
                v = dp[j] + cost[j][i]
                if v < best:
                    best = v
            dp[i] = best

        return dp[n]
# @lc code=end
