#
# @lc app=leetcode id=3493 lang=python3
#
# [3493] Properties Graph
#

# @lc code=start
class Solution:
    def numberOfComponents(self, properties: List[List[int]], k: int) -> int:
        n = len(properties)
        
        # Convert each property list to a set for faster intersection computation
        property_sets = [set(prop) for prop in properties]
        
        # Build adjacency list representation of the graph
        adj = [[] for _ in range(n)]
        
        # Check all pairs of nodes to see if they should be connected
        for i in range(n):
            for j in range(i + 1, n):
                # Count intersection of properties
                intersection_count = len(property_sets[i] & property_sets[j])
                
                # If intersection count is at least k, add an edge
                if intersection_count >= k:
                    adj[i].append(j)
                    adj[j].append(i)
        
        # Use DFS to count connected components
        visited = [False] * n
        components = 0
        
        def dfs(node):
            visited[node] = True
            for neighbor in adj[node]:
                if not visited[neighbor]:
                    dfs(neighbor)
        
        # Count connected components
        for i in range(n):
            if not visited[i]:
                dfs(i)
                components += 1
        
        return components
# @lc code=end