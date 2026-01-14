#
# @lc app=leetcode id=3493 lang=python3
#
# [3493] Properties Graph
#

# @lc code=start
class Solution:
    def numberOfComponents(self, properties: List[List[int]], k: int) -> int:
        n = len(properties)
        
        # Convert each property array to a set of distinct elements
        prop_sets = [set(p) for p in properties]
        
        # Union-Find with path compression
        parent = list(range(n))
        
        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]
        
        def union(x, y):
            px, py = find(x), find(y)
            if px != py:
                parent[px] = py
        
        # Check all pairs
        for i in range(n):
            for j in range(i + 1, n):
                # Count distinct integers common to both
                if len(prop_sets[i] & prop_sets[j]) >= k:
                    union(i, j)
        
        # Count connected components
        return len(set(find(i) for i in range(n)))
# @lc code=end