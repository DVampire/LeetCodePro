#
# @lc app=leetcode id=3425 lang=python3
#
# [3425] Longest Special Path
#

# @lc code=start
import sys

# Increase recursion depth for deep trees
sys.setrecursionlimit(100000)

class Solution:
    def longestSpecialPath(self, edges: List[List[int]], nums: List[int]) -> List[int]:
        n = len(nums)
        adj = [[] for _ in range(n)]
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))
            
        # pos[val] stores the depth index of the last occurrence of val in the current path
        # using a list is faster than a dict given the constraints on nums[i]
        # Max value in nums is 5*10^4
        max_val = 0
        for x in nums:
            max_val = max(max_val, x)
        pos = [-1] * (max_val + 1)
        
        # dist_stack[i] stores the cumulative distance from root to the node at depth i
        dist_stack = []
        
        # Result: [max_len, min_nodes]
        # Initialize with [0, 1] because a single node is a valid path of length 0
        res = [0, 1]
        
        def dfs(u, p, depth, curr_dist, start_index):
            val = nums[u]
            prev_index = pos[val]
            
            # The valid path must start after the previous occurrence of the current value
            # Also must respect constraints from ancestors (captured in start_index)
            new_start_index = start_index
            if prev_index != -1 and prev_index >= start_index:
                new_start_index = prev_index + 1
            
            # Calculate length and node count for the longest special path ending at u
            # The path starts at new_start_index in the stack
            # Distance at start of path: dist_stack[new_start_index]
            # Note: dist_stack currently has entries up to depth-1.
            # If new_start_index == depth, distance is curr_dist.
            
            dist_at_start = 0
            if new_start_index == depth:
                dist_at_start = curr_dist
            else:
                dist_at_start = dist_stack[new_start_index]
                
            path_len = curr_dist - dist_at_start
            node_count = depth - new_start_index + 1
            
            if path_len > res[0]:
                res[0] = path_len
                res[1] = node_count
            elif path_len == res[0]:
                if node_count < res[1]:
                    res[1] = node_count
            
            # Update state for children
            pos[val] = depth
            dist_stack.append(curr_dist)
            
            for v, w in adj[u]:
                if v != p:
                    dfs(v, u, depth + 1, curr_dist + w, new_start_index)
            
            # Backtrack
            dist_stack.pop()
            pos[val] = prev_index

        dfs(0, -1, 0, 0, 0)
        return res

# @lc code=end