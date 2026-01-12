#
# @lc app=leetcode id=3331 lang=python3
#
# [3331] Find Subtree Sizes After Changes
#

# @lc code=start
import collections
from typing import List

class Solution:
    def findSubtreeSizes(self, parent: List[int], s: str) -> List[int]:
        n = len(parent)
        if n == 0:
            return []
        
        # 1. Build original adjacency list
        adj = [[] for _ in range(n)]
        for i in range(1, n):
            adj[parent[i]].append(i)
        
        # 2. Find new parents based on the closest ancestor with the same character
        new_parent = list(parent)
        last_seen = [-1] * 26
        stack = [(0, False)]  # (node, is_processed_exit)
        history = []  # To restore last_seen values during iterative DFS backtracking
        
        while stack:
            u, processed = stack.pop()
            char_idx = ord(s[u]) - 97
            if not processed:
                # Entering node u: find closest ancestor and update last_seen
                old_val = last_seen[char_idx]
                if old_val != -1:
                    new_parent[u] = old_val
                
                # Save current state for backtracking and update last_seen
                history.append(old_val)
                last_seen[char_idx] = u
                
                # Push exit marker and children to stack
                stack.append((u, True))
                for v in reversed(adj[u]):
                    stack.append((v, False))
            else:
                # Exiting node u: restore the previous last_seen value
                last_seen[char_idx] = history.pop()
        
        # 3. Build new adjacency list for the modified tree
        new_adj = [[] for _ in range(n)]
        for i in range(1, n):
            new_adj[new_parent[i]].append(i)
        
        # 4. Calculate subtree sizes using iterative post-order traversal
        ans = [1] * n
        order = []
        queue = collections.deque([0])
        while queue:
            u = queue.popleft()
            order.append(u)
            for v in new_adj[u]:
                queue.append(v)
        
        # Process nodes in reverse discovery order (from leaves to root)
        for u in reversed(order):
            p = new_parent[u]
            if p != -1:
                ans[p] += ans[u]
        
        return ans
# @lc code=end