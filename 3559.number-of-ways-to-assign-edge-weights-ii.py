#
# @lc app=leetcode id=3559 lang=python3
#
# [3559] Number of Ways to Assign Edge Weights II
#
# @lc code=start
class Solution:
    def assignEdgeWeights(self, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        from collections import defaultdict, deque
        
        MOD = 10**9 + 7
        
        # Build the tree
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
        
        # Function to find path length from u to v using BFS
        def find_path_length(u, v):
            if u == v:
                return 0
            
            visited = set([u])
            queue = deque([(u, 0)])
            
            while queue:
                node, dist = queue.popleft()
                
                for neighbor in graph[node]:
                    if neighbor not in visited:
                        if neighbor == v:
                            return dist + 1
                        visited.add(neighbor)
                        queue.append((neighbor, dist + 1))
            
            return 0
        
        result = []
        for u, v in queries:
            k = find_path_length(u, v)
            if k == 0:
                result.append(0)
            else:
                # Number of ways to have odd sum = 2^(k-1)
                result.append(pow(2, k - 1, MOD))
        
        return result
# @lc code=end