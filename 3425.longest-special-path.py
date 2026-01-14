#
# @lc app=leetcode id=3425 lang=python3
#
# [3425] Longest Special Path
#

# @lc code=start
from typing import List
import sys

class Solution:
    def longestSpecialPath(self, edges: List[List[int]], nums: List[int]) -> List[int]:
        sys.setrecursionlimit(60000)
        n = len(nums)
        
        # Build adjacency list
        adj = [[] for _ in range(n)]
        for u, v, length in edges:
            adj[u].append((v, length))
            adj[v].append((u, length))
        
        max_length = 0
        min_nodes = 1
        
        # path_dist[i] = cumulative distance from root to i-th node in current path
        path_dist = [0]
        # last_occurrence[val] = index in path where value was last seen
        last_occurrence = {}
        
        def dfs(node, parent, left):
            nonlocal max_length, min_nodes
            
            val = nums[node]
            cur_idx = len(path_dist) - 1
            
            # Save old occurrence for backtracking
            old_occurrence = last_occurrence.get(val, -1)
            
            # Update left pointer if duplicate found
            if val in last_occurrence:
                left = max(left, last_occurrence[val] + 1)
            
            # Update last occurrence
            last_occurrence[val] = cur_idx
            
            # Calculate path length and nodes for path ending at current node
            path_length = path_dist[cur_idx] - path_dist[left]
            num_nodes = cur_idx - left + 1
            
            # Update answer
            if path_length > max_length or (path_length == max_length and num_nodes < min_nodes):
                max_length = path_length
                min_nodes = num_nodes
            
            # DFS to children
            for neighbor, weight in adj[node]:
                if neighbor != parent:
                    path_dist.append(path_dist[-1] + weight)
                    dfs(neighbor, node, left)
                    path_dist.pop()
            
            # Backtrack: restore last_occurrence
            if old_occurrence == -1:
                del last_occurrence[val]
            else:
                last_occurrence[val] = old_occurrence
        
        dfs(0, -1, 0)
        
        return [max_length, min_nodes]
# @lc code=end