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
        # Step 1: Build original tree adjacency list
        adj = [[] for _ in range(n)]
        for i in range(1, n):
            adj[parent[i]].append(i)
        
        new_parent = [-1] * n
        last_seen = [-1] * 26
        
        # Step 2: Iterative DFS to find new parents for all nodes
        # stack stores (node, is_pre_order, val_to_restore)
        stack = [(0, True, -1)]
        while stack:
            u, is_pre, old_val = stack.pop()
            char_idx = ord(s[u]) - ord('a')
            
            if is_pre:
                # Finding the closest ancestor with the same character
                if u != 0:
                    closest = last_seen[char_idx]
                    new_parent[u] = closest if closest != -1 else parent[u]
                
                # Save current state for restoration in post-order
                current_char_ancestor = last_seen[char_idx]
                last_seen[char_idx] = u
                stack.append((u, False, current_char_ancestor))
                
                # Add children to stack
                for v in adj[u]:
                    stack.append((v, True, -1))
            else:
                # Restore the last_seen value for this character after visiting subtree
                last_seen[char_idx] = old_val
        
        # Step 3: Build new tree adjacency list based on new_parent
        new_adj = [[] for _ in range(n)]
        for i in range(1, n):
            new_adj[new_parent[i]].append(i)
            
        # Step 4: Calculate subtree sizes iteratively
        ans = [1] * n
        order = []
        traversal_stack = [0]
        # Standard pre-order to get the processing order
        while traversal_stack:
            u = traversal_stack.pop()
            order.append(u)
            for v in new_adj[u]:
                traversal_stack.append(v)
        
        # Process nodes in reverse pre-order (post-order)
        for u in reversed(order):
            p = new_parent[u]
            if p != -1:
                ans[p] += ans[u]
                
        return ans
# @lc code=end