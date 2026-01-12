#
# @lc app=leetcode id=3486 lang=python3
#
# [3486] Longest Special Path II
#

# @lc code=start
import sys
from collections import defaultdict

# Increase recursion depth for deep trees
sys.setrecursionlimit(200000)

class Solution:
    def longestSpecialPath(self, edges: list[list[int]], nums: list[int]) -> list[int]:
        n = len(nums)
        adj = [[] for _ in range(n)]
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))
            
        # Fenwick tree to track indices in S
        bit = [0] * (n + 1)
        def bit_update(idx, val):
            idx += 1 # 1-indexed
            while idx <= n:
                bit[idx] += val
                idx += idx & (-idx)
                
        def bit_query_total():
            idx = n
            s = 0
            while idx > 0:
                s += bit[idx]
                idx -= idx & (-idx)
            return s
            
        def bit_find_kth(k):
            idx = 0
            current_sum = 0
            for i in range(16, -1, -1):
                next_idx = idx + (1 << i)
                if next_idx <= n and current_sum + bit[next_idx] < k:
                    idx = next_idx
                    current_sum += bit[idx]
            return idx # Returns 0-indexed position (since we used 1-indexed in bit)

        max_len = -1
        min_nodes = float('inf')
        
        val_indices = defaultdict(list)
        path_dists = [0] # Prefix sums of weights
        
        def dfs(u, p, current_dist, depth):
            nonlocal max_len, min_nodes
            
            val = nums[u]
            added_idx = -1
            if val_indices[val]:
                added_idx = val_indices[val][-1]
                bit_update(added_idx, 1)
            
            val_indices[val].append(depth)
            path_dists.append(current_dist)
            
            total_s = bit_query_total()
            if total_s < 2:
                min_i = 0
            else:
                # Second largest is the (total_s - 1)-th smallest
                max2 = bit_find_kth(total_s - 1)
                min_i = max2 + 1
            
            curr_path_len = current_dist - path_dists[min_i]
            curr_num_nodes = depth - min_i + 1
            
            if curr_path_len > max_len:
                max_len = curr_path_len
                min_nodes = curr_num_nodes
            elif curr_path_len == max_len:
                if curr_num_nodes < min_nodes:
                    min_nodes = curr_num_nodes
            
            for v, w in adj[u]:
                if v != p:
                    dfs(v, u, current_dist + w, depth + 1)
            
            # Backtrack
            path_dists.pop()
            val_indices[val].pop()
            if added_idx != -1:
                bit_update(added_idx, -1)

        dfs(0, -1, 0, 0)
        return [max_len, min_nodes]
# @lc code=end