#
# @lc app=leetcode id=3515 lang=python3
#
# [3515] Shortest Path in a Weighted Tree
#
# @lc code=start
class Solution:
    def treeQueries(self, n: int, edges: List[List[int]], queries: List[List[int]]) -> List[int]:
        from collections import defaultdict, deque
        
        # Build adjacency list
        graph = defaultdict(dict)
        for u, v, w in edges:
            graph[u][v] = w
            graph[v][u] = w
        
        def find_distance(target):
            if target == 1:
                return 0
            
            # BFS from node 1 to target
            queue = deque([(1, 0)])  # (node, distance)
            visited = set([1])
            
            while queue:
                node, dist = queue.popleft()
                
                for neighbor, weight in graph[node].items():
                    if neighbor not in visited:
                        if neighbor == target:
                            return dist + weight
                        visited.add(neighbor)
                        queue.append((neighbor, dist + weight))
            
            return -1
        
        result = []
        
        for query in queries:
            if query[0] == 1:
                # Update query
                u, v, w_new = query[1], query[2], query[3]
                graph[u][v] = w_new
                graph[v][u] = w_new
            else:
                # Distance query
                x = query[1]
                result.append(find_distance(x))
        
        return result
# @lc code=end