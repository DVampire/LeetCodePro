#
# @lc app=leetcode id=3575 lang=python3
#
# [3575] Maximum Good Subtree Score
#

from typing import List

# @lc code=start
class Solution:
    def goodSubtreeSum(self, vals: List[int], par: List[int]) -> int:
        n = len(vals)
        adj = [[] for _ in range(n)]
        for i in range(1, n):
            adj[par[i]].append(i)
        MOD = 10**9 + 7
        INF = 10**18 + 10**12
        total = [0]

        def get_mask(val: int) -> int:
            seen = 0
            s = str(val)
            for ch in s:
                d = ord(ch) - ord('0')
                if seen & (1 << d):
                    return -1
                seen |= (1 << d)
            return seen

        def dfs(u: int) -> List[int]:
            mask_u = get_mask(vals[u])
            dp_children = [-INF] * 1024
            dp_children[0] = 0
            for v in adj[u]:
                child_dp = dfs(v)
                new_dp = [-INF] * 1024
                active_prev = [p for p in range(1024) if dp_children[p] != -INF]
                active_child = [c for c in range(1024) if child_dp[c] != -INF]
                for p in active_prev:
                    ps = dp_children[p]
                    for c in active_child:
                        if (p & c) == 0:
                            nm = p | c
                            new_dp[nm] = max(new_dp[nm], ps + child_dp[c])
                dp_children = new_dp
            # dp_u without u
            dp_u = dp_children[:]
            # add u if possible
            if mask_u != -1:
                val_u = vals[u]
                active_here = [m for m in range(1024) if dp_children[m] != -INF]
                for m in active_here:
                    if (m & mask_u) == 0:
                        nm = m | mask_u
                        dp_u[nm] = max(dp_u[nm], dp_children[m] + val_u)
            # max_sc
            max_sc = 0
            for i in range(1024):
                if dp_u[i] > max_sc:
                    max_sc = dp_u[i]
            total[0] = (total[0] + max_sc) % MOD
            return dp_u

        dfs(0)
        return total[0]

# @lc code=end
