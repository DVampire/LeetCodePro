#
# @lc app=leetcode id=3544 lang=python3
#
# [3544] Subtree Inversion Sum
#

# @lc code=start
from typing import List

class Solution:
    def subtreeInversionSum(self, edges: List[List[int]], nums: List[int], k: int) -> int:
        n = len(nums)
        adj = [[] for _ in range(n)]
        for a, b in edges:
            adj[a].append(b)
            adj[b].append(a)
        
        self.dp = [[0] * k for _ in range(n)]
        self.nums = nums
        self.k = k
        
        def dfs(u: int, par: int) -> None:
            children = [v for v in adj[u] if v != par]
            for c in children:
                dfs(c, u)
            
            for m in range(self.k):
                # Not inverting u
                m_child_no = max(0, m - 1)
                sum_child_no = 0
                for c in children:
                    sum_child_no += self.dp[c][m_child_no]
                contrib_no = self.nums[u] + sum_child_no
                
                max_val = contrib_no
                
                # Inverting u, only if m == 0
                if m == 0:
                    m_child_yes = max(0, self.k - 1)
                    sum_child_yes = 0
                    for c in children:
                        sum_child_yes += self.dp[c][m_child_yes]
                    contrib_yes = -self.nums[u] - sum_child_yes
                    max_val = max(contrib_no, contrib_yes)
                
                self.dp[u][m] = max_val
        
        dfs(0, -1)
        return self.dp[0][0]

# @lc code=end