#
# @lc app=leetcode id=3515 lang=python3
#
# [3515] Shortest Path in a Weighted Tree
#

# @lc code=start
from typing import List

class Solution:
    def treeQueries(self, n: int, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        adj = [[] for _ in range(n + 1)]
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))
        
        tin = [0] * (n + 1)
        tout = [0] * (n + 1)
        dist = [0] * (n + 1)
        parent = [0] * (n + 1)
        edge_weight_to_parent = [0] * (n + 1)
        visited_count = [0] * (n + 1)
        
        # Iterative DFS to compute tin, tout, and initial distances
        timer = 0
        stack = [(1, 0, 0)] # node, parent, current_distance
        while stack:
            u, p, d = stack[-1]
            if tin[u] == 0:
                timer += 1
                tin[u] = timer
                dist[u] = d
            
            u_adj = adj[u]
            found_child = False
            curr_idx = visited_count[u]
            while curr_idx < len(u_adj):
                v, w = u_adj[curr_idx]
                curr_idx += 1
                if v != p:
                    visited_count[u] = curr_idx
                    parent[v] = u
                    edge_weight_to_parent[v] = w
                    stack.append((v, u, d + w))
                    found_child = True
                    break
            
            if not found_child:
                visited_count[u] = curr_idx
                tout[u] = timer
                stack.pop()
        
        # Binary Indexed Tree for range updates and point queries
        bit = [0] * (n + 2)
        bit_len = n + 2
        ans = []
        
        for q in queries:
            if q[0] == 1: # Update Query
                u, v, w_new = q[1], q[2], q[3]
                # Identify the child node in the edge (u, v)
                child = v if parent[v] == u else u
                delta = w_new - edge_weight_to_parent[child]
                edge_weight_to_parent[child] = w_new
                
                # Range update [tin[child], tout[child]] in BIT
                idx = tin[child]
                while idx < bit_len:
                    bit[idx] += delta
                    idx += idx & (-idx)
                
                idx = tout[child] + 1
                while idx < bit_len:
                    bit[idx] -= delta
                    idx += idx & (-idx)
            else: # Distance Query
                x = q[1]
                # Point query at tin[x] (prefix sum of deltas)
                res = 0
                idx = tin[x]
                while idx > 0:
                    res += bit[idx]
                    idx -= idx & (-idx)
                ans.append(dist[x] + res)
                
        return ans
# @lc code=end