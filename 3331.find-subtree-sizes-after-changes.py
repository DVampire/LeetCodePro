#
# @lc app=leetcode id=3331 lang=python3
#
# [3331] Find Subtree Sizes After Changes
#

# @lc code=start
import sys

class Solution:
    def findSubtreeSizes(self, parent: List[int], s: str) -> List[int]:
        # Increase recursion depth to handle deep trees up to 10^5 nodes
        sys.setrecursionlimit(200000)
        
        n = len(parent)
        # Step 1: Build the original adjacency list
        adj = [[] for _ in range(n)]
        for i in range(1, n):
            adj[parent[i]].append(i)
        
        new_parent = [-1] * n
        # last_seen stores the nearest ancestor for each character 'a'-'z'
        last_seen = [-1] * 26
        
        # Step 2: DFS to find new parents based on original tree structure
        def find_new_parents(u):
            char_idx = ord(s[u]) - 97
            
            # Find the closest ancestor with the same character
            ancestor = last_seen[char_idx]
            if ancestor != -1:
                new_parent[u] = ancestor
            else:
                new_parent[u] = parent[u]
            
            # Update last_seen for current character and recurse to children
            old_val = last_seen[char_idx]
            last_seen[char_idx] = u
            for v in adj[u]:
                find_new_parents(v)
            # Backtrack: restore last_seen for other branches
            last_seen[char_idx] = old_val
            
        find_new_parents(0)
        
        # Step 3: Build the adjacency list for the modified tree
        new_adj = [[] for _ in range(n)]
        for i in range(1, n):
            # new_parent[i] is the updated parent of node i
            new_adj[new_parent[i]].append(i)
            
        subtree_size = [0] * n
        
        # Step 4: DFS to calculate subtree sizes in the modified tree
        def calculate_sizes(u):
            curr_size = 1
            for v in new_adj[u]:
                curr_size += calculate_sizes(v)
            subtree_size[u] = curr_size
            return curr_size
            
        calculate_sizes(0)
        return subtree_size
# @lc code=end