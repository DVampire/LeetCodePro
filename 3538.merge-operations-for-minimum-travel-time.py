#
# @lc app=leetcode id=3538 lang=python3
#
# [3538] Merge Operations for Minimum Travel Time
#

from typing import List
import math

# @lc code=start
class Solution:
    def minTravelTime(self, l: int, n: int, k: int, position: List[int], time: List[int]) -> int:
        INF = 10**30

        # Prefix sums of time to query sum(time[a..b]) quickly.
        pref = [0] * (n + 1)
        for i in range(n):
            pref[i + 1] = pref[i] + time[i]

        def sum_time(a: int, b: int) -> int:
            """Sum of time[a..b], inclusive. Assumes 0 <= a <= b < n."""
            return pref[b + 1] - pref[a]

        # dp[prev][cur][used]
        dp = [[[INF] * (k + 1) for _ in range(n)] for __ in range(n)]

        # Initialize: first kept sign after 0 is j
        for j in range(1, n):
            used = j - 1  # removed indices 1..j-1
            if used <= k:
                dp[0][j][used] = (position[j] - position[0]) * time[0]

        # Transitions
        for used in range(k + 1):
            for prev in range(n):
                for cur in range(prev + 1, n):
                    base = dp[prev][cur][used]
                    if base >= INF:
                        continue
                    if cur == n - 1:
                        continue  # already at the end

                    # Final time stored at `cur` depends only on (prev, cur)
                    t_cur = sum_time(prev + 1, cur)

                    for nxt in range(cur + 1, n):
                        add_removed = nxt - cur - 1
                        used2 = used + add_removed
                        if used2 > k:
                            break
                        cost_add = (position[nxt] - position[cur]) * t_cur
                        if base + cost_add < dp[cur][nxt][used2]:
                            dp[cur][nxt][used2] = base + cost_add

        ans = INF
        for prev in range(n - 1):
            ans = min(ans, dp[prev][n - 1][k])
        return ans
# @lc code=end
