#
# @lc app=leetcode id=3435 lang=python3
#
# [3435] Frequencies of Shortest Supersequences
#

# @lc code=start
from typing import List
from collections import defaultdict

class Solution:
    def supersequences(self, words: List[str]) -> List[List[int]]:
        # Find unique characters
        chars = set()
        for w in words:
            chars.update(w)
        chars = sorted(chars)
        char_to_idx = {c: i for i, c in enumerate(chars)}
        n = len(chars)
        
        if n == 0:
            return [[0] * 26]
        
        # Build graph and identify self-loops
        edges = [set() for _ in range(n)]
        has_self_loop = [False] * n
        
        for w in words:
            a, b = char_to_idx[w[0]], char_to_idx[w[1]]
            if a == b:
                has_self_loop[a] = True
            else:
                edges[a].add(b)
        
        # Hard characters: those without self-loop
        hard_chars = [i for i in range(n) if not has_self_loop[i]]
        num_hard = len(hard_chars)
        hard_idx = {hard_chars[i]: i for i in range(num_hard)}
        
        # Build subgraph among hard characters
        hard_edges = [[] for _ in range(num_hard)]
        for i, hi in enumerate(hard_chars):
            for j in edges[hi]:
                if j in hard_idx:
                    hard_edges[i].append(hard_idx[j])
        
        # Check if removing a subset (FVS) makes graph acyclic
        def is_acyclic(fvs_mask):
            remaining = ((1 << num_hard) - 1) ^ fvs_mask if num_hard > 0 else 0
            if remaining == 0:
                return True
            
            in_degree = [0] * num_hard
            for u in range(num_hard):
                if not (remaining & (1 << u)):
                    continue
                for v in hard_edges[u]:
                    if remaining & (1 << v):
                        in_degree[v] += 1
            
            queue = [u for u in range(num_hard) if (remaining & (1 << u)) and in_degree[u] == 0]
            count = 0
            while queue:
                u = queue.pop()
                count += 1
                for v in hard_edges[u]:
                    if not (remaining & (1 << v)):
                        continue
                    in_degree[v] -= 1
                    if in_degree[v] == 0:
                        queue.append(v)
            
            return count == bin(remaining).count('1')
        
        # Group masks by popcount for early termination
        masks_by_popcount = defaultdict(list)
        for mask in range(1 << num_hard):
            masks_by_popcount[bin(mask).count('1')].append(mask)
        
        # Find minimum FVS size and collect all masks with that size
        min_masks = []
        for size in range(num_hard + 1):
            for mask in masks_by_popcount[size]:
                if is_acyclic(mask):
                    min_masks.append(mask)
            if min_masks:
                break
        
        # Generate frequency arrays
        result_set = set()
        for mask in min_masks:
            freq = [0] * 26
            for i, c in enumerate(chars):
                idx = ord(c) - ord('a')
                if has_self_loop[i]:
                    freq[idx] = 2
                elif i in hard_idx and (mask & (1 << hard_idx[i])):
                    freq[idx] = 2
                else:
                    freq[idx] = 1
            result_set.add(tuple(freq))
        
        return [list(f) for f in result_set]
# @lc code=end