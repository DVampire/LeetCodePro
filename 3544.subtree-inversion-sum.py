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
        graph = [[] for _ in range(n)]
        
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
        
        # Build tree structure from root
        root = 0
        children = [[] for _ in range(n)]
        visited = [False] * n
        
        def build_tree(node):
            visited[node] = True
            for neighbor in graph[node]:
                if not visited[neighbor]:
                    children[node].append(neighbor)
                    build_tree(neighbor)
        
        build_tree(root)
        
        memo = {}
        
        def dfs(node, last_inv_dist, is_inverted):
            state = (node, last_inv_dist, is_inverted)
            if state in memo:
                return memo[state]
            
            # Current node's value based on inversion state from ancestors
            current_val = -nums[node] if is_inverted else nums[node]
            
            # Option 1: Don't invert this node
            option1 = current_val
            new_dist = min(last_inv_dist + 1, k + 1)
            for child in children[node]:
                option1 += dfs(child, new_dist, is_inverted)
            
            # Option 2: Invert this node (if allowed by distance constraint)
            option2 = float('-inf')
            if last_inv_dist >= k:
                inverted_val = nums[node] if is_inverted else -nums[node]
                option2 = inverted_val
                for child in children[node]:
                    option2 += dfs(child, 1, not is_inverted)
            
            result = max(option1, option2)
            memo[state] = result
            return result
        
        return dfs(0, k, False)
# @lc code=end