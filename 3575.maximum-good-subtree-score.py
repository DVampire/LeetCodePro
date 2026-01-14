#
# @lc app=leetcode id=3575 lang=python3
#
# [3575] Maximum Good Subtree Score
#

# @lc code=start
class Solution:
    def goodSubtreeSum(self, vals: List[int], par: List[int]) -> int:
        MOD = 10**9 + 7
        n = len(vals)
        
        # Build adjacency list for children
        children = [[] for _ in range(n)]
        for i in range(1, n):
            children[par[i]].append(i)
        
        def get_digit_mask(val):
            """Returns bitmask of digits in val, or -1 if any digit repeats"""
            mask = 0
            while val > 0:
                digit = val % 10
                if mask & (1 << digit):
                    return -1
                mask |= (1 << digit)
                val //= 10
            return mask
        
        max_scores = [0] * n
        
        def dfs(node):
            """Returns dict {mask: max_sum} for subtree of node"""
            # Start with empty subset
            dp = {0: 0}
            
            # Try including current node
            node_mask = get_digit_mask(vals[node])
            if node_mask != -1:
                dp[node_mask] = vals[node]
            
            # Process each child
            for child in children[node]:
                child_dp = dfs(child)
                
                # Merge child_dp into dp
                new_dp = dict(dp)
                for curr_mask, curr_sum in dp.items():
                    for child_mask, child_sum in child_dp.items():
                        if child_mask == 0:  # skip empty
                            continue
                        if curr_mask & child_mask == 0:  # no conflict
                            new_mask = curr_mask | child_mask
                            new_sum = curr_sum + child_sum
                            if new_mask not in new_dp or new_dp[new_mask] < new_sum:
                                new_dp[new_mask] = new_sum
                dp = new_dp
            
            # Record max score for this node
            max_scores[node] = max(dp.values())
            
            return dp
        
        dfs(0)
        
        return sum(max_scores) % MOD
# @lc code=end