#
# @lc app=leetcode id=3493 lang=python3
#
# [3493] Properties Graph
#

# @lc code=start
class Solution:
    def numberOfComponents(self, properties: List[List[int]], k: int) -> int:
        n = len(properties)
        # Convert each property list to a set for distinct element counting
        # and faster intersection operations.
        prop_sets = [set(p) for p in properties]
        
        # Union-Find (DSU) initialization
        parent = list(range(n))
        self.count = n
        
        def find(i):
            if parent[i] != i:
                parent[i] = find(parent[i])
            return parent[i]
        
        def union(i, j):
            root_i = find(i)
            root_j = find(j)
            if root_i != root_j:
                parent[root_i] = root_j
                self.count -= 1
                return True
            return False
        
        # Iterate through all pairs of nodes
        for i in range(n):
            for j in range(i + 1, n):
                # Calculate size of intersection of distinct elements
                # Since sets only store distinct elements, len(s1 & s2) works perfectly
                intersection_size = len(prop_sets[i].intersection(prop_sets[j]))
                
                if intersection_size >= k:
                    union(i, j)
                    
        return self.count
# @lc code=end