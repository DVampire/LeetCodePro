#
# @lc app=leetcode id=3538 lang=python3
#
# [3538] Merge Operations for Minimum Travel Time
#

# @lc code=start
from typing import List

class Solution:
    def minTravelTime(self, l: int, n: int, k: int, position: List[int], time: List[int]) -> int:
        INF = 10**18
        dp = [[[INF] * 101 for _ in range(k + 1)] for _ in range(n)]
        prefix = [0] * (n + 1)
        for i in range(1, n + 1):
            prefix[i] = prefix[i - 1] + time[i - 1]
        dp[0][0][time[0]] = 0
        for i in range(1, n):
            for prev in range(i):
                num_remove = i - prev - 1
                sum_t = prefix[i + 1] - prefix[prev + 1]
                if sum_t > 100:
                    continue
                dist = position[i] - position[prev]
                for r_prev in range(k + 1):
                    for t_prev in range(101):
                        if dp[prev][r_prev][t_prev] == INF:
                            continue
                        r_new = r_prev + num_remove
                        if r_new > k:
                            continue
                        added = dist * t_prev
                        new_cost = dp[prev][r_prev][t_prev] + added
                        if new_cost < dp[i][r_new][sum_t]:
                            dp[i][r_new][sum_t] = new_cost
        ans = INF
        for t in range(101):
            if dp[n - 1][k][t] < ans:
                ans = dp[n - 1][k][t]
        return ans

# @lc code=end