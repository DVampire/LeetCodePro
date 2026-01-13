#
# @lc app=leetcode id=3310 lang=python3
#
# [3310] Remove Methods From Project
#
# @lc code=start
class Solution:
    def remainingMethods(self, n: int, k: int, invocations: List[List[int]]) -> List[int]:
        from collections import deque
        
        # Build adjacency list
        graph = [[] for _ in range(n)]
        for a, b in invocations:
            graph[a].append(b)
        
        # Find all suspicious methods (reachable from k) using BFS
        suspicious = set()
        queue = deque([k])
        suspicious.add(k)
        
        while queue:
            node = queue.popleft()
            for neighbor in graph[node]:
                if neighbor not in suspicious:
                    suspicious.add(neighbor)
                    queue.append(neighbor)
        
        # Check if any non-suspicious method invokes a suspicious method
        for a, b in invocations:
            if a not in suspicious and b in suspicious:
                # Cannot remove suspicious methods
                return list(range(n))
        
        # Can remove suspicious methods
        return [i for i in range(n) if i not in suspicious]
# @lc code=end