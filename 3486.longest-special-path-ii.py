#
# @lc app=leetcode id=3486 lang=python3
#
# [3486] Longest Special Path II
#

# @lc code=start
from collections import defaultdict, deque
from typing import List

class Solution:
    def longestSpecialPath(self, edges: List[List[int]], nums: List[int]) -> List[int]:
        n = len(nums)
        
        # Build adjacency list
        graph = defaultdict(list)
        for u, v, length in edges:
            graph[u].append((v, length))
            graph[v].append((u, length))
        
        # Root the tree at node 0 - find parent-child relationships
        children = defaultdict(list)
        visited = [False] * n
        queue = deque([0])
        visited[0] = True
        
        while queue:
            node = queue.popleft()
            for neighbor, length in graph[node]:
                if not visited[neighbor]:
                    visited[neighbor] = True
                    children[node].append((neighbor, length))
                    queue.append(neighbor)
        
        def is_valid(value_count):
            dup_count = 0
            for count in value_count.values():
                if count > 2:
                    return False
                if count == 2:
                    dup_count += 1
            return dup_count <= 1
        
        max_length = 0
        min_nodes = float('inf')
        
        # Try each node as starting point
        for start in range(n):
            def dfs(node, value_count, path_length, node_count):
                nonlocal max_length, min_nodes
                
                # Check if current path is valid (must have at least 2 nodes)
                if node_count >= 2 and is_valid(value_count):
                    if path_length > max_length:
                        max_length = path_length
                        min_nodes = node_count
                    elif path_length == max_length:
                        min_nodes = min(min_nodes, node_count)
                
                # Continue DFS to children
                for child, length in children[node]:
                    child_val = nums[child]
                    value_count[child_val] += 1
                    
                    # Only continue if still valid
                    if is_valid(value_count):
                        dfs(child, value_count, path_length + length, node_count + 1)
                    
                    value_count[child_val] -= 1
                    if value_count[child_val] == 0:
                        del value_count[child_val]
            
            value_count = defaultdict(int)
            value_count[nums[start]] = 1
            dfs(start, value_count, 0, 1)
        
        return [max_length, min_nodes]
# @lc code=end