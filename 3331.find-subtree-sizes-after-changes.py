#
# @lc app=leetcode id=3331 lang=python3
#
# [3331] Find Subtree Sizes After Changes
#

# @lc code=start
from typing import List

class Solution:
    def findSubtreeSizes(self, parent: List[int], s: str) -> List[int]:
        n = len(parent)
        # Step 1: Build adjacency list for the original tree
        adj = [[] for _ in range(n)]
        for i in range(1, n):
            adj[parent[i]].append(i)
        
        # Step 2: Determine new parent for each node using DFS
        new_parent = list(parent)
        last_seen = [-1] * 26
        history = [-1] * n
        order = []
        
        # Iterative DFS to find the closest ancestor with the same character
        stack = [(0, 0)] # (node, state: 0 for entry, 1 for exit)
        while stack:
            u, state = stack.pop()
            char_idx = ord(s[u]) - ord('a')
            if state == 0:
                # Upon entering node u
                if last_seen[char_idx] != -1:
                    new_parent[u] = last_seen[char_idx]
                
                # Save current state for backtracking and update last_seen
                history[u] = last_seen[char_idx]
                last_seen[char_idx] = u
                order.append(u)
                
                # Prepare to exit node u after visiting children
                stack.append((u, 1))
                # Add children to stack to process them
                for v in adj[u]:
                    stack.append((v, 0))
            else:
                # Upon exiting node u, restore last_seen to its previous state
                last_seen[char_idx] = history[u]
        
        # Step 3: Calculate subtree sizes in the new tree using the topological order
        # Since the new parent was an ancestor in the original tree, the original 
        # pre-order (stored in 'order') remains a valid topological sort.
        subtree_sizes = [1] * n
        for u in reversed(order):
            p = new_parent[u]
            if p != -1:
                subtree_sizes[p] += subtree_sizes[u]
                
        return subtree_sizes
# @lc code=end