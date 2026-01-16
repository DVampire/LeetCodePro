#
# @lc app=leetcode id=3425 lang=python3
#
# [3425] Longest Special Path
#

# @lc code=start
class Solution:
    def longestSpecialPath(self, edges: List[List[int]], nums: List[int]) -> List[int]:
        from collections import defaultdict
        
        # Build adjacency list
        graph = defaultdict(list)
        for u, v, length in edges:
            graph[u].append((v, length))
            graph[v].append((u, length))
        
        # Global variables to track results
        max_length = 0
        min_nodes_for_max = float('inf')
        
        # DFS function
        def dfs(node, parent, path_values, current_length, node_count):
            nonlocal max_length, min_nodes_for_max
            
            # Check if current node value already exists in path
            if nums[node] in path_values:
                # Cannot extend path further from here
                return
            
            # Add current node to path
            path_values.add(nums[node])
            
            # Update global results if needed
            if current_length > max_length:
                max_length = current_length
                min_nodes_for_max = node_count
            elif current_length == max_length:
                min_nodes_for_max = min(min_nodes_for_max, node_count)
            
            # Recurse on children
            for child, edge_length in graph[node]:
                if child != parent:  # Prevent going back to parent in undirected graph
                    dfs(child, node, path_values, current_length + edge_length, node_count + 1)
            
            # Backtrack: remove current node value from path_values
            path_values.remove(nums[node])
        
        # Start DFS from root (node 0) with empty path values set
        dfs(0, -1, set(), 0, 1)
        
        return [max_length, min_nodes_for_max]
# @lc code=end