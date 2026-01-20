#
# @lc app=leetcode id=3486 lang=python3
#
# [3486] Longest Special Path II
#

# @lc code=start
from typing import List
import collections
import sys
sys.setrecursionlimit(10**5 + 10)

class Solution:
    def longestSpecialPath(self, edges: List[List[int]], nums: List[int]) -> List[int]:
        n = len(nums)
        adj = [[] for _ in range(n)]
        for ui, vi, li in edges:
            adj[ui].append((vi, li))
            adj[vi].append((ui, li))
        max_length = 0
        min_node_count = n + 1

        def update(length: int, node_count: int):
            nonlocal max_length, min_node_count
            if length > max_length:
                max_length = length
                min_node_count = node_count
            elif length == max_length:
                min_node_count = min(min_node_count, node_count)

        def backtrack(u: int, parent: int, cur_length: int, cur_nodes: int, counter: collections.Counter, has_duplicate: int):
            update(cur_length, cur_nodes)
            for v, length in adj[u]:
                if v == parent:
                    continue
                val = nums[v]
                old_freq = counter.get(val, 0)
                new_freq = old_freq + 1
                new_has_dup = has_duplicate
                is_bad = False
                if new_freq > 2:
                    is_bad = True
                elif new_freq == 2:
                    if has_duplicate == 1:
                        is_bad = True
                    else:
                        new_has_dup = 1
                if not is_bad:
                    counter[val] = new_freq
                    backtrack(v, u, cur_length + length, cur_nodes + 1, counter, new_has_dup)
                    counter[val] = old_freq
                    if old_freq == 0:
                        del counter[val]

        for i in range(n):
            counter = collections.Counter({nums[i]: 1})
            backtrack(i, -1, 0, 1, counter, 0)
        return [max_length, min_node_count]

# @lc code=end