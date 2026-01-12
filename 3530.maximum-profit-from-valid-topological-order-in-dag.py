#
# @lc app=leetcode id=3530 lang=python3
#
# [3530] Maximum Profit from Valid Topological Order in DAG
#

# @lc code=start
class Solution:
    def maxProfit(self, n: int, edges: List[List[int]], score: List[int]) -> int:
        # Precompute predecessors for each node as a bitmask
        pre = [0] * n
        for u, v in edges:
            pre[v] |= (1 << u)
        
        # dp[mask] will store the maximum profit for the set of nodes in 'mask'
        # Initialize with -1 to represent unreachable states
        dp = [-1] * (1 << n)
        dp[0] = 0
        
        # Iterate through all possible masks
        for mask in range(1 << n):
            curr_profit = dp[mask]
            if curr_profit == -1:
                continue
            
            # The next node to be added will be at position k + 1
            k_plus_1 = mask.bit_count() + 1
            
            # Try adding each node u that is not already in the mask
            for u in range(n):
                if not (mask & (1 << u)):
                    # Check if all predecessors of node u are in the current mask
                    if (pre[u] & mask) == pre[u]:
                        new_mask = mask | (1 << u)
                        new_profit = curr_profit + score[u] * k_plus_1
                        # Update dp table if a higher profit is found
                        if new_profit > dp[new_mask]:
                            dp[new_mask] = new_profit
                            
        return dp[(1 << n) - 1]
# @lc code=end