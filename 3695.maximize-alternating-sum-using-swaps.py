#
# @lc app=leetcode id=3695 lang=python3
#
# [3695] Maximize Alternating Sum Using Swaps
#
# @lc code=start
class Solution:
    def maxAlternatingSum(self, nums: List[int], swaps: List[List[int]]) -> int:
        n = len(nums)
        parent = list(range(n))
        
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            px, py = find(x), find(y)
            if px != py:
                parent[px] = py
        
        # Build connected components
        for p, q in swaps:
            union(p, q)
        
        # Group indices by their root
        from collections import defaultdict
        components = defaultdict(list)
        for i in range(n):
            components[find(i)].append(i)
        
        # Calculate the maximum alternating sum
        result = 0
        for indices in components.values():
            # Get values at these indices
            values = [nums[i] for i in indices]
            
            # Count even indices in this component
            even_count = sum(1 for i in indices if i % 2 == 0)
            
            # Sort values in descending order
            values.sort(reverse=True)
            
            # Assign largest values to even indices (positive contribution)
            # and smallest values to odd indices (negative contribution)
            for i in range(even_count):
                result += values[i]
            for i in range(even_count, len(values)):
                result -= values[i]
        
        return result
# @lc code=end