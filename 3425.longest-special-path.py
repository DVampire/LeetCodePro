#
# @lc app=leetcode id=3425 lang=python3
#
# [3425] Longest Special Path
#

# @lc code=start
class Solution:
    def longestSpecialPath(self, edges: List[List[int]], nums: List[int]) -> List[int]:
        n = len(nums)
        adj = [[] for _ in range(n)]
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))
        
        # last_seen stores the index in the current path for each value
        # Constraints say nums[i] <= 50000
        last_seen = [-1] * 50001
        path_nodes = []
        path_dists = []
        ans = [0, 1] # [max_length, min_nodes]
        
        # stack stores (u, p, current_dist, top_idx, state)
        # state 0: pre-order, state 1: post-order
        stack = [(0, -1, 0, 0, 0)]
        
        while stack:
            u, p, d, top_or_old, state = stack.pop()
            v = nums[u]
            
            if state == 0:
                # Pre-order traversal
                old_idx = last_seen[v]
                # The start of the special path must be after any previous occurrence of the current value
                new_top = max(top_or_old, old_idx + 1)
                
                # Add current node to path tracking
                path_nodes.append(u)
                path_dists.append(d)
                last_seen[v] = len(path_nodes) - 1
                
                # Calculate length and node count for the special path ending at u
                # starting from the highest valid ancestor
                length = d - path_dists[new_top]
                count = len(path_nodes) - new_top
                
                if length > ans[0]:
                    ans[0] = length
                    ans[1] = count
                elif length == ans[0]:
                    if count < ans[1]:
                        ans[1] = count
                
                # Record backtrack step
                stack.append((u, p, d, old_idx, 1))
                
                # Explore children
                for neighbor, weight in adj[u]:
                    if neighbor != p:
                        stack.append((neighbor, u, d + weight, new_top, 0))
            else:
                # Post-order (Backtracking)
                # Restore the state for the parent
                last_seen[v] = top_or_old
                path_nodes.pop()
                path_dists.pop()
                
        return ans
# @lc code=end