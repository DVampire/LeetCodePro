#
# @lc app=leetcode id=3575 lang=python3
#
# [3575] Maximum Good Subtree Score
#

# @lc code=start
import sys

# Increase recursion depth for deep trees
sys.setrecursionlimit(2000)

class Solution:
    def goodSubtreeSum(self, vals: List[int], par: List[int]) -> int:
        n = len(vals)
        children = [[] for _ in range(n)]
        for i, p in enumerate(par):
            if p != -1:
                children[p].append(i)
        
        # Precompute masks and validity for each node
        node_masks = [0] * n
        node_valid = [False] * n
        
        for i, x in enumerate(vals):
            s = str(x)
            mask = 0
            valid = True
            used = 0
            for c in s:
                d = int(c)
                if (used >> d) & 1:
                    valid = False
                    break
                used |= (1 << d)
            if valid:
                node_masks[i] = used
                node_valid[i] = True
                
        ans = 0
        MOD = 10**9 + 7
        
        def dfs(u):
            # Initialize DP state for the current node u
            # dp[mask] = max_score
            # Start with the empty set (score 0, mask 0)
            current_dp = {0: 0}
            
            # If the current node itself is valid, add it as a starting state
            if node_valid[u]:
                current_dp[node_masks[u]] = vals[u]
            
            # Iterate through all children and merge their DP states
            for v in children[u]:
                child_dp = dfs(v)
                
                # Convert to lists for iteration
                l1 = list(current_dp.items())
                l2 = list(child_dp.items())
                
                # Temporary array for merging to avoid hash map overhead in the inner loop
                # 1024 is 2^10, covering all possible digit masks
                tmp = [-1] * 1024
                
                # Merge logic: combine disjoint masks
                for m1, s1 in l1:
                    for m2, s2 in l2:
                        if (m1 & m2) == 0:
                            nm = m1 | m2
                            ns = s1 + s2
                            if ns > tmp[nm]:
                                tmp[nm] = ns
                
                # Rebuild the sparse dictionary for the next iteration
                current_dp = {}
                for m in range(1024):
                    if tmp[m] != -1:
                        current_dp[m] = tmp[m]

            # The max score for the subtree rooted at u is the max value in current_dp
            # Note: The empty set (score 0) is always present, so max is at least 0.
            # If all values are positive, non-empty sets will have score > 0.
            mx = 0
            for s in current_dp.values():
                if s > mx:
                    mx = s
            
            nonlocal ans
            ans = (ans + mx) % MOD
            
            return current_dp

        dfs(0)
        return ans

# @lc code=end