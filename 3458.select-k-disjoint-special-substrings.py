#
# @lc app=leetcode id=3458 lang=python3
#
# [3458] Select K Disjoint Special Substrings
#

# @lc code=start
import math

class Solution:
    def maxSubstringLength(self, s: str, k: int) -> bool:
        n = len(s)
        if n == 0:
            return k == 0
        L = [-1] * 26
        R = [-1] * 26
        for i in range(n):
            c = ord(s[i]) - ord('a')
            if L[c] == -1:
                L[c] = i
        for i in range(n - 1, -1, -1):
            c = ord(s[i]) - ord('a')
            if R[c] == -1:
                R[c] = i
        starts = [L[c] for c in range(26) if L[c] != -1]
        LB = [0] * n
        RB = [0] * n
        for i in range(n):
            c = ord(s[i]) - ord('a')
            LB[i] = L[c]
            RB[i] = R[c]
        # Sparse table for min LB
        logn = int(math.log2(n)) + 1 if n > 0 else 1
        st_min = [[0] * logn for _ in range(n)]
        st_max = [[0] * logn for _ in range(n)]
        for i in range(n):
            st_min[i][0] = LB[i]
            st_max[i][0] = RB[i]
        for j in range(1, logn):
            for i in range(n - (1 << j) + 1):
                st_min[i][j] = min(st_min[i][j - 1], st_min[i + (1 << (j - 1))][j - 1])
                st_max[i][j] = max(st_max[i][j - 1], st_max[i + (1 << (j - 1))][j - 1])
        def query_min(left: int, right: int) -> int:
            if left > right:
                return float('inf')
            length = right - left + 1
            k = int(math.log2(length))
            return min(st_min[left][k], st_min[right - (1 << k) + 1][k])
        def query_max(left: int, right: int) -> int:
            if left > right:
                return float('-inf')
            length = right - left + 1
            k = int(math.log2(length))
            return max(st_max[left][k], st_max[right - (1 << k) + 1][k])
        dp = [0] * (n + 1)
        for i in range(1, n + 1):
            dp[i] = dp[i - 1]
            endd = i - 1
            for j in starts:
                if j > endd:
                    continue
                minlb = query_min(j, endd)
                maxrb = query_max(j, endd)
                if minlb >= j and maxrb <= endd and not (j == 0 and endd == n - 1):
                    dp[i] = max(dp[i], dp[j] + 1)
        return dp[n] >= k

# @lc code=end
