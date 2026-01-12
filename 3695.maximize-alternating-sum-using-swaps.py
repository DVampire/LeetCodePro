#
# @lc app=leetcode id=3695 lang=python3
#
# [3695] Maximize Alternating Sum Using Swaps
#

# @lc code=start
from typing import List
import collections

class Solution:
    def maxAlternatingSum(self, nums: List[int], swaps: List[List[int]]) -> int:
        n = len(nums)
        parent = list(range(n))
        
        def find(i):
            if parent[i] == i:
                return i
            parent[i] = find(parent[i])
            return parent[i]
        
        def union(i, j):
            root_i = find(i)
            root_j = find(j)
            if root_i != root_j:
                parent[root_i] = root_j
        
        for u, v in swaps:
            union(u, v)
            
        components = collections.defaultdict(list)
        for i in range(n):
            components[find(i)].append(i)
            
        total_sum = 0
        for comp in components.values():
            vals = sorted([nums[i] for i in comp], reverse=True)
            even_count = sum(1 for i in comp if i % 2 == 0)
            
            # Place the largest values at even indices and smallest at odd indices
            # even_count values will be added, (len(comp) - even_count) will be subtracted
            for i in range(even_count):
                total_sum += vals[i]
            for i in range(even_count, len(comp)):
                total_sum -= vals[i]
                
        return total_sum
# @lc code=end