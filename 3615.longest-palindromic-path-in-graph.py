#
# @lc app=leetcode id=3615 lang=python3
#
# [3615] Longest Palindromic Path in Graph
#
# @lc code=start
class Solution:
    def maxLen(self, n: int, edges: List[List[int]], label: str) -> int:
        # Build adjacency list
        graph = [[] for _ in range(n)]
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
        
        max_length = 1  # At least one node
        
        def dfs(node, visited_mask, path):
            nonlocal max_length
            
            # Check if current path is palindrome
            if path == path[::-1]:
                max_length = max(max_length, len(path))
            
            # Try to extend the path
            for neighbor in graph[node]:
                if not (visited_mask & (1 << neighbor)):
                    dfs(neighbor, visited_mask | (1 << neighbor), path + label[neighbor])
        
        # Try starting from each node
        for start in range(n):
            dfs(start, 1 << start, label[start])
        
        return max_length
# @lc code=end