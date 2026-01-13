#
# @lc app=leetcode id=3425 lang=python3
#
# [3425] Longest Special Path
#

# @lc code=start
class Solution:
    def longestSpecialPath(self, edges: List[List[int]], nums: List[int]) -> List[int]:
        n = len(nums)
        
        # Build adjacency list
        graph = [[] for _ in range(n)]
        for u, v, length in edges:
            graph[u].append((v, length))
            graph[v].append((u, length))
        
        # Build tree structure (parent -> children)
        children = [[] for _ in range(n)]
        visited = [False] * n
        
        def build_tree(node):
            visited[node] = True
            for neighbor, length in graph[node]:
                if not visited[neighbor]:
                    children[node].append((neighbor, length))
                    build_tree(neighbor)
        
        build_tree(0)
        
        max_length = 0
        min_nodes = 1
        
        def dfs(node, current_length, node_count, seen_values):
            nonlocal max_length, min_nodes
            
            # Update result for current path
            if current_length > max_length:
                max_length = current_length
                min_nodes = node_count
            elif current_length == max_length:
                min_nodes = min(min_nodes, node_count)
            
            # Try to extend path to children
            for child, edge_length in children[node]:
                if nums[child] not in seen_values:
                    seen_values.add(nums[child])
                    dfs(child, current_length + edge_length, node_count + 1, seen_values)
                    seen_values.remove(nums[child])
        
        # Explore all possible starting points
        def explore_all(node):
            # Start a new path from this node
            dfs(node, 0, 1, {nums[node]})
            # Recursively explore children
            for child, _ in children[node]:
                explore_all(child)
        
        explore_all(0)
        
        return [max_length, min_nodes]
# @lc code=end