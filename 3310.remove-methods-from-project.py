#
# @lc app=leetcode id=3310 lang=python3
#
# [3310] Remove Methods From Project
#

# @lc code=start
from collections import deque
from typing import List

class Solution:
    def remainingMethods(self, n: int, k: int, invocations: List[List[int]]) -> List[int]:
        # Build adjacency list
        adj = [[] for _ in range(n)]
        for u, v in invocations:
            adj[u].append(v)
            
        # Find all suspicious methods using BFS starting from k
        suspicious = [False] * n
        suspicious[k] = True
        queue = deque([k])
        
        while queue:
            curr = queue.popleft()
            for neighbor in adj[curr]:
                if not suspicious[neighbor]:
                    suspicious[neighbor] = True
                    queue.append(neighbor)
                    
        # Check if any non-suspicious method invokes a suspicious method
        can_remove = True
        for u, v in invocations:
            # If u is not suspicious but v is suspicious, we cannot remove the group
            if not suspicious[u] and suspicious[v]:
                can_remove = False
                break
        
        # If we can remove them, return non-suspicious methods
        if can_remove:
            return [i for i in range(n) if not suspicious[i]]
        else:
            # Otherwise return all methods
            return list(range(n))

# @lc code=end