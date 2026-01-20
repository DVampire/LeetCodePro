#
# @lc app=leetcode id=3425 lang=python3
#
# [3425] Longest Special Path
#

from typing import List
import sys
from collections import defaultdict

# @lc code=start
class Solution:
    def longestSpecialPath(self, edges: List[List[int]], nums: List[int]) -> List[int]:
        sys.setrecursionlimit(10**5 + 10)
        n = len(nums)
        adj = [[] for _ in range(n)]
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))
        
        self.max_len_here = [0] * n
        self.nodes_here = [1] * n
        self.left = 0
        self.path = []
        self.prefix = []
        self.pos_lists = defaultdict(list)
        
        def dfs(curr: int, par: int, edge_w: int) -> None:
            self.path.append(curr)
            if self.prefix:
                self.prefix.append(self.prefix[-1] + edge_w)
            else:
                self.prefix.append(0)
            idx = len(self.path) - 1
            val = nums[curr]
            
            new_left = self.left
            if val in self.pos_lists and self.pos_lists[val]:
                prev_idx = self.pos_lists[val][-1]
                if prev_idx >= new_left:
                    new_left = prev_idx + 1
            
            old_left = self.left
            self.left = new_left
            
            self.pos_lists[val].append(idx)
            
            this_len = self.prefix[-1] - self.prefix[self.left]
            this_nodes = idx - self.left + 1
            self.max_len_here[curr] = this_len
            self.nodes_here[curr] = this_nodes
            
            for neigh, w in adj[curr]:
                if neigh != par:
                    dfs(neigh, curr, w)
            
            self.pos_lists[val].pop()
            if not self.pos_lists[val]:
                del self.pos_lists[val]
            self.left = old_left
            
            self.prefix.pop()
            self.path.pop()
        
        dfs(0, -1, 0)
        
        global_max = max(self.max_len_here)
        min_nodes = min(self.nodes_here[i] for i in range(n) if self.max_len_here[i] == global_max)
        
        return [global_max, min_nodes]
        
# @lc code=end
