#
# @lc app=leetcode id=3695 lang=python3
#
# [3695] Maximize Alternating Sum Using Swaps
#

# @lc code=start
class Solution:
    def maxAlternatingSum(self, nums: List[int], swaps: List[List[int]]) -> int:
        n = len(nums)
        adj = [[] for _ in range(n)]
        for u, v in swaps:
            adj[u].append(v)
            adj[v].append(u)
        
        visited = [False] * n
        total_sum = 0
        
        for i in range(n):
            if not visited[i]:
                # Start a traversal to find the connected component
                component_indices = []
                stack = [i]
                visited[i] = True
                
                while stack:
                    u = stack.pop()
                    component_indices.append(u)
                    for v in adj[u]:
                        if not visited[v]:
                            visited[v] = True
                            stack.append(v)
                
                # Collect values and count even/odd positions in this component
                values = []
                even_slots = 0
                odd_slots = 0
                
                for idx in component_indices:
                    values.append(nums[idx])
                    if idx % 2 == 0:
                        even_slots += 1
                    else:
                        odd_slots += 1
                
                # Sort values descending
                values.sort(reverse=True)
                
                # Assign largest values to even slots (positive contribution)
                # Assign smallest values to odd slots (negative contribution)
                
                # The first even_slots values are added
                for k in range(even_slots):
                    total_sum += values[k]
                
                # The remaining odd_slots values are subtracted
                for k in range(even_slots, len(values)):
                    total_sum -= values[k]
                    
        return total_sum
# @lc code=end