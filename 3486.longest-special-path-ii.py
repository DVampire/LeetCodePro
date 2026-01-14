#
# @lc app=leetcode id=3486 lang=python3
#
# [3486] Longest Special Path II
#

# @lc code=start
from collections import defaultdict
import bisect
import sys
from typing import List

class Solution:
    def longestSpecialPath(self, edges: List[List[int]], nums: List[int]) -> List[int]:
        sys.setrecursionlimit(60000)
        n = len(nums)
        adj = defaultdict(list)
        for u, v, length in edges:
            adj[u].append((v, length))
            adj[v].append((u, length))
        
        pos = defaultdict(list)
        path_dist = [0]
        dup_first_positions = []
        
        best_length = 0
        best_nodes = 1
        
        def dfs(node, parent, depth, blocked):
            nonlocal best_length, best_nodes
            
            v = nums[node]
            old_pos_len = len(pos[v])
            pos[v].append(depth)
            
            new_blocked = blocked
            
            if old_pos_len >= 2:
                new_blocked = max(new_blocked, pos[v][-3])
                old_first = pos[v][-3]
                new_first = pos[v][-2]
                idx = bisect.bisect_left(dup_first_positions, old_first)
                dup_first_positions.pop(idx)
                bisect.insort(dup_first_positions, new_first)
            elif old_pos_len == 1:
                bisect.insort(dup_first_positions, pos[v][-2])
            
            L = new_blocked + 1
            if len(dup_first_positions) >= 2:
                L = max(L, dup_first_positions[-2] + 1)
            
            current_length = path_dist[depth] - path_dist[L]
            current_nodes = depth - L + 1
            
            if current_length > best_length or (current_length == best_length and current_nodes < best_nodes):
                best_length = current_length
                best_nodes = current_nodes
            
            for child, edge_len in adj[node]:
                if child != parent:
                    path_dist.append(path_dist[-1] + edge_len)
                    dfs(child, node, depth + 1, new_blocked)
                    path_dist.pop()
            
            pos[v].pop()
            if old_pos_len >= 2:
                old_first = pos[v][-2]
                new_first = pos[v][-1]
                idx = bisect.bisect_left(dup_first_positions, new_first)
                dup_first_positions.pop(idx)
                bisect.insort(dup_first_positions, old_first)
            elif old_pos_len == 1:
                idx = bisect.bisect_left(dup_first_positions, pos[v][-1])
                dup_first_positions.pop(idx)
        
        dfs(0, -1, 0, -1)
        
        return [best_length, best_nodes]
# @lc code=end