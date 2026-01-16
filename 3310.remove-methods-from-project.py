#
# @lc app=leetcode id=3310 lang=python3
#
# [3310] Remove Methods From Project
#

# @lc code=start
class Solution:
    def remainingMethods(self, n: int, k: int, invocations: List[List[int]]) -> List[int]:
        # Build adjacency list for the graph
        graph = [[] for _ in range(n)]
        reverse_graph = [[] for _ in range(n)]
        
        for a, b in invocations:
            graph[a].append(b)
            reverse_graph[b].append(a)
        
        # Find all suspicious methods using DFS from method k
        suspicious = set()
        stack = [k]
        suspicious.add(k)
        
        while stack:
            node = stack.pop()
            for neighbor in graph[node]:
                if neighbor not in suspicious:
                    suspicious.add(neighbor)
                    stack.append(neighbor)
        
        # Check if any method outside suspicious set points to a method inside suspicious set
        for method in range(n):
            if method not in suspicious:
                for invoked_method in graph[method]:
                    if invoked_method in suspicious:
                        # Cannot remove suspicious methods
                        return list(range(n))
        
        # If we can remove, return all methods except suspicious ones
        result = []
        for i in range(n):
            if i not in suspicious:
                result.append(i)
        
        return result
# @lc code=end