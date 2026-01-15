#
# @lc app=leetcode id=3575 lang=python3
#
# [3575] Maximum Good Subtree Score
#

# @lc code=start
from typing import List

class Solution:
    def goodSubtreeSum(self, vals: List[int], par: List[int]) -> int:
        MOD = 10**9 + 7
        n = len(vals)
        
        # Build tree
        children = [[] for _ in range(n)]
        for i in range(1, n):
            children[par[i]].append(i)
        
        # Compute digit mask for each value (-1 if invalid due to duplicate digits)
        def get_mask(v):
            mask = 0
            while v > 0:
                d = v % 10
                if mask & (1 << d):
                    return -1
                mask |= (1 << d)
                v //= 10
            return mask
        
        masks = [get_mask(v) for v in vals]
        
        result = 0
        
        def dfs(u):
            nonlocal result
            
            # dp[mask] = max sum with digit mask `mask`
            dp = {0: 0}
            
            # Include current node if valid
            if masks[u] != -1:
                dp[masks[u]] = vals[u]
            
            # Process children
            for c in children[u]:
                child_dp = dfs(c)
                
                # Merge dp with child_dp
                new_dp = {}
                for m1, v1 in dp.items():
                    for m2, v2 in child_dp.items():
                        if (m1 & m2) == 0:
                            m = m1 | m2
                            if m not in new_dp or new_dp[m] < v1 + v2:
                                new_dp[m] = v1 + v2
                dp = new_dp
            
            # maxScore[u] = max value in dp
            result = (result + max(dp.values())) % MOD
            
            return dp
        
        dfs(0)
        return result
# @lc code=end