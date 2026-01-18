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
        # Step 1: Build the graph
        adj = [[] for _ in range(n)]
        for u, v in invocations:
            adj[u].append(v)
        
        # Step 2: Find all suspicious methods using BFS
        suspicious = [False] * n
        suspicious[k] = True
        queue = deque([k])
        
        while queue:
            curr = queue.popleft()
            for neighbor in adj[curr]:
                if not suspicious[neighbor]:
                    suspicious[neighbor] = True
                    queue.append(neighbor)
        
        # Step 3: Check if any non-suspicious method invokes a suspicious method
        can_remove = True
        for u, v in invocations:
            # If caller is not suspicious but callee is suspicious
            if not suspicious[u] and suspicious[v]:
                can_remove = False
                break
        
        # Step 4: Return the result
        if not can_remove:
            return list(range(n))
        
        return [i for i in range(n) if not suspicious[i]]

# @lc code=end